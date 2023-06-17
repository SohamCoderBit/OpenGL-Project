#pragma once
#include "OpenGL.h"

class IndexBuffer
{
public:

	IndexBuffer();
	~IndexBuffer();
	void Bind() const;
	void UnBind() const;
	void AddBufferData(const void* Data, unsigned int Size);
	inline unsigned int GetCount() { return m_Count; }

private:

	unsigned int m_RendererID;
	unsigned int m_Count;
};
