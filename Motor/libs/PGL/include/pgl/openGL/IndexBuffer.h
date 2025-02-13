#pragma once

typedef unsigned int uint;

class IndexBuffer
{
private:
	uint m_ID;
	uint m_Count;
public:
	IndexBuffer(const uint* data, uint count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline uint GetCount() const { return m_Count; }
};