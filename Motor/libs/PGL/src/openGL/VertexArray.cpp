#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_ID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_ID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	//bind vertex Array
	Bind();

	//bind buffer
	vb.Bind();

	//setup layout
	const auto& elements = layout.GetElements();
	uint offset = 0;
	for (uint i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}


}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_ID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}