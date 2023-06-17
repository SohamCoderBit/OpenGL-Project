#pragma once
#include <iostream>

#include "OpenGL.h"
#include "VertexArrayLayout.h"
#include "VertexBuffer.h"

#include <vector>

class VertexArray
{
public:
	
	VertexArray();
	~VertexArray();
	void Bind();
	void UnBind();
	void AddBuffer(VertexBuffer* vertexbuffer, const VertexArrayLayout& ElementLayout);


private:

	unsigned int m_VertexArrayObjectID;
};

