#pragma once

#include <unordered_map>
#include "glm/glm.hpp"

typedef unsigned int uint;

struct ShaderProgramSource {
	const char* vertex_source;
	const char* fragment_source;
};


class Shader
{
private:
	uint m_ID = 0;
	
	const char* m_Vert_path;
	const char* m_Frag_path;

	std::unordered_map<const char*, int> m_UniformCache;
public:
	Shader(const char* vertex_shader, const char* fragment_shader, bool isPath = true);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//set uniforms
	void SetUniform1i(const char* name, int value);
	void SetUniform1f(const char* name, float value);
	void SetUniform4f(const char* name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const char* name, const glm::mat4& matrix);

private :
	ShaderProgramSource parseShader();

	uint CreateShader(const char* vertexShader, const char* fragmentShader);
	uint compileShader(const char* source, uint type);

	int GetUniformLocation(const char* name);
};

