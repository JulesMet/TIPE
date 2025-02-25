#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const uint* data, uint count)
    : m_Count(count)
{
    static_assert(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_ID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_ID));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}