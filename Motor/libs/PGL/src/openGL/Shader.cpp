#include "Shader.h"

#include "Logger.h"

#include <fstream>
#include <string>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

Shader::Shader(const char* vertex_shader, const char* fragment_shader)
	: m_Vert_path(vertex_shader), m_Frag_path(fragment_shader)
{
	ShaderProgramSource source = parseShader();
	m_ID = CreateShader(source.vertex_source, source.fragment_source);
}

Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

void Shader::Bind() const
{
	glUseProgram(m_ID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
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
	uint program = glCreateProgram();

	uint vert = compileShader(vertexShader, GL_VERTEX_SHADER);
	uint frag = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vert);
	glDeleteShader(frag);

	return program;
}

uint Shader::compileShader(const char* source, uint type)
{
	uint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		Logger l(Logger::FILTER_ERROR);

		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);

		std::string s = std::string("Failed to compile the ") + std::string(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			+ std::string(" shader !\n") + std::string(message);
		l.Log(s.c_str(), Logger::Log_Level::ERROR, Logger_Color{ Logger_Color::Colors::RED });
		delete[](message);
		glDeleteShader(shader);
		return EXIT_FAILURE;
	}

	return shader;
}

int Shader::GetUniformLocation(const char* name)
{
	return 0;
}
