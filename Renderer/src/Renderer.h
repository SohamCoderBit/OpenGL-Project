#pragma once
#include <iostream>

#include "OpenGL.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Texture.h"

class Renderer
{
public:

	Renderer();
	void Draw();
	void CameraInit();
	~Renderer();

private:

	VertexBuffer* vertexbuffer = nullptr;
	VertexArray* vertexArray = nullptr;
	VertexArrayLayout Layout;
	IndexBuffer* indexbuffer = nullptr;
	Shader* shader = nullptr;
	Texture* BrickTexture;

	float Rotation = 30;

private:

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
};