#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &m_RendererID);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::AddBufferData(const void* Data, unsigned int count)
{
    m_Count = count;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, Data, GL_STATIC_DRAW);
}
