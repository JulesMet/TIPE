#pragma once

typedef unsigned int uint;

#include <glad\glad.h>
#include <GLFW\glfw3.h>

class VertexBuffer
{
private:
	GLuint m_ID;

	//float* m_Data;
	//GLenum m_Usage;
	
public :

	VertexBuffer(const float* data, size_t size, GLuint usage = GL_STATIC_DRAW);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	GLuint ID() const { return m_ID; }
};

