#include "FrameBuffers.h"
#include <iostream>

void FrameBuffers::Create(uint32_t Height, uint32_t Width)
{
	glGenFramebuffers(1, &m_FrameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

	glGenTextures(1, &m_FrameBufferTextureID);
	glBindTexture(GL_TEXTURE_2D, m_FrameBufferTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FrameBufferTextureID, 0);

	glGenRenderbuffers(1, &m_RenderBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferID);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

	UnBind();
}

void FrameBuffers::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
}

void FrameBuffers::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void FrameBuffers::ReScale(float Height, float Width)
{
	glBindTexture(GL_TEXTURE_2D, m_FrameBufferTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FrameBufferTextureID, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferID);
}

void FrameBuffers::Deletion()
{
	glDeleteFramebuffers(1, &m_FrameBufferID);
	glDeleteTextures(1, &m_FrameBufferTextureID);
	glDeleteRenderbuffers(1, &m_RenderBufferID);
}
