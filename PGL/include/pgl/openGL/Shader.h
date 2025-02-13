#pragma once

#include <unordered_map>

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
	Shader(const char* vertex_shader, const char* fragment_shader);
	~Shader();

	void Bind() const;
	void Unbind() const;

private :
	ShaderProgramSource parseShader();

	uint CreateShader(const char* vertexShader, const char* fragmentShader);
	uint compileShader(const char* source, uint type);

	int GetUniformLocation(const char* name);
};

