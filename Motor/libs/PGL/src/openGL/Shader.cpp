#include "Shader.h"

#include "Logger.h"

#include <fstream>
#include <string>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Renderer.h"

Shader::Shader(const char* vertex_shader, const char* fragment_shader, bool isPath)
	: m_Vert_path(vertex_shader), m_Frag_path(fragment_shader)
{
	if(isPath)
	{
		ShaderProgramSource source = parseShader();
		m_ID = CreateShader(source.vertex_source, source.fragment_source);
	}
	else
	{
		m_ID = CreateShader(vertex_shader, fragment_shader);
	}
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_ID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_ID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

ShaderProgramSource Shader::parseShader()
{
	std::string vert, frag;

	{
		std::ifstream stream(m_Vert_path);

		std::string line;
		while (getline(stream, line))
		{
			vert += line + '\n';
		}

		stream.close();
	}


	{
		std::ifstream stream(m_Frag_path);
		std::string line;
		while (getline(stream, line))
		{
			frag += line + '\n';
		}

		stream.close();
	}

	return { vert.c_str(), frag.c_str()};
}

uint Shader::CreateShader(const char* vertexShader, const char* fragmentShader)
{
	GLCall(uint program = glCreateProgram());

	uint vert = compileShader(vertexShader, GL_VERTEX_SHADER);
	uint frag = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

	GLCall(glAttachShader(program, vert));
	GLCall(glAttachShader(program, frag));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vert));
	GLCall(glDeleteShader(frag));

	return program;
}

uint Shader::compileShader(const char* source, uint type)
{
	uint shader = glCreateShader(type);
	GLCall(glShaderSource(shader, 1, &source, nullptr));
	GLCall(glCompileShader(shader));

	int result;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		Logger l(Logger::FILTER_ERROR);

		int length;
		GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)_malloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(shader, length, &length, message));

		std::string s = std::string("Failed to compile the ") + std::string(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			+ std::string(" shader !\n") + std::string(message);
		l.Log(s.c_str(), Logger::Log_Level::ERROR, Logger_Color{ Logger_Color::Colors::RED });
		delete[](message);
		GLCall(glDeleteShader(shader));
		return EXIT_FAILURE;
	}

	return shader;
}


void Shader::SetUniform1i(const char* name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const char* name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const char* name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const char* name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const char* name)
{
	if (m_UniformCache.find(name) != m_UniformCache.end())
		return m_UniformCache[name];

	GLCall(int location = glGetUniformLocation(m_ID, name));
	if (location == -1)
	{
		Logger l(Logger::FILTER_INFO);
		std::string msg = std::string("Warning: uniform ") + std::string(name) + std::string(" doesn't exist!");
		l.Log(msg.c_str(), Logger::WARN, Logger_Color{ Logger_Color::Colors::YELLOW });
		//std::cout << "Warning: uniform " + name + " doesn't exist!" << std::endl;
	}

	m_UniformCache[name] = location;
	return location;
}