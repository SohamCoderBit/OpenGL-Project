#pragma once
#include "OpenGL.h"

class VertexBuffer
{
public:

	VertexBuffer();
	void Bind() const;
	void UnBind() const;
	void AddBufferData(const void* Data, unsigned int Size);
	~VertexBuffer();

private:

	unsigned int m_RendererID;
};