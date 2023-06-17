#include "VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VertexArrayObjectID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_VertexArrayObjectID);
}

void VertexArray::Bind()
{
	glBindVertexArray(m_VertexArrayObjectID);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(VertexBuffer* vertexbuffer ,const VertexArrayLayout& ElementLayout)
{
	const auto& element = ElementLayout.m_LayoutVector;
	unsigned int offset = 0;
	for (unsigned int i = 0; i < element.size(); i++)
	{
		glVertexAttribPointer(i, element[i].Count, element[i].Type, element[i].Normalized, ElementLayout.m_Stride, (const void*)offset);
		//std::cout << "i :: " << offset << std::endl
		offset += element[i].Count * VertexArrayLayout::Layout::GetSizeOfDataType(element[i].Type);
		glEnableVertexAttribArray(i);
	}

}

