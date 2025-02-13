#include "VertexBuffer.h"



VertexBuffer::VertexBuffer(const float* data, size_t size, GLuint usage) :
	m_ID(0)//, m_Data(data), m_Usage(usage)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_VERTEX_ARRAY, m_ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_VERTEX_ARRAY, m_ID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_VERTEX_ARRAY, 0);
}
