#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_RendererID);
    
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::AddBufferData(const void* Data, unsigned int Size)
{
    glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}
