#pragma once
#include "OpenGL.h"

class FrameBuffers
{
public:

	void Create(uint32_t Height , uint32_t Width);
	void Bind();
	void UnBind();
	void ReScale(float Height , float Width);
	unsigned int GetFrameBufferTextureID() { return m_FrameBufferTextureID; }
	void Deletion();

private:
	unsigned int m_FrameBufferID;
	unsigned int m_FrameBufferTextureID;
	unsigned int m_RenderBufferID;

};