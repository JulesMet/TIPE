#pragma once

#include <vector>
#include <stdexcept>

#include "Renderer.h"

typedef unsigned int uint;

struct VertexBufferElement
{
	uint type;
	uint count;
	unsigned char normalized;

	static uint GetSizeOfType(uint type)
	{
		switch (type)
		{
		case GL_FLOAT:			return sizeof(GLfloat);
		case GL_UNSIGNED_INT:	return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:	return sizeof(GLbyte);
		}

		std::runtime_error("Error wrong type passed to GetSizeOfType\n");
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	uint m_Stride;

public:
	VertexBufferLayout()
		: m_Stride(0) {
	}
	//~VertexBufferLayout();

	template<typename T>
	void Push(uint count)
	{
		//static_assert(false);
		std::runtime_error(false);
	}

	template<>
	void Push<float>(uint count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * sizeof(GLfloat);
	}

	template<>
	void Push<unsigned int>(uint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * sizeof(GLuint);
	}

	template<>
	void Push<unsigned char>(uint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * sizeof(GLbyte);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline uint GetStride() const { return m_Stride; }

};

