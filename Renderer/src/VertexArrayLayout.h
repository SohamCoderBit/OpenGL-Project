#pragma once
#include "OpenGL.h"

#include <vector>


class VertexArrayLayout
{
public:
	
	struct Layout
	{
		unsigned int Type;
		unsigned int Count;
		unsigned char Normalized;

		static unsigned int  GetSizeOfDataType(const unsigned int& m_Type)
		{
			switch (m_Type)
			{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_BYTE: return 1;
			}
		}
	};

	std::vector<Layout> m_LayoutVector;
	unsigned int m_Stride = 0;



	void AddLayoutData(unsigned int Type , unsigned int count)
	{
		m_LayoutVector.push_back({ Type , count , GL_FALSE });
		m_Stride += count * Layout::GetSizeOfDataType(GL_FLOAT);
	}


};
