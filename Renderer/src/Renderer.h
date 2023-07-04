#pragma once
#include <iostream>
#include <string>	

#include "OpenGL.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Texture.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

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