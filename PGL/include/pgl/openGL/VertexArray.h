#pragma once

#include "VertexBuffer.h"

typedef unsigned int uint;

class VertexBufferLayout;

class VertexArray {
private:
	uint m_ID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};