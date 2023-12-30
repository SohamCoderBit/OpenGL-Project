#pragma once
#include <iostream>
#include <string>	

#include "OpenGL.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "FrameBuffers.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Renderer
{
public:

	Renderer();
	void Init();
	void Draw();
	//void Update();
	//static void KeyInputHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
	//void HandleKey(int key, int action);
	~Renderer() = default;

private:

	Scope<VertexBuffer> vertexbuffer ;
	Scope<VertexArray> vertexArray ;
	VertexArrayLayout Layout;
	Scope<IndexBuffer> indexbuffer ;
	Scope<FrameBuffers> framebuffer ;
	Scope<Shader> shader;
	Scope<Texture> BrickTexture;

	float Rotation = 30;

private:

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	glm::vec3 m_CameraPosition = glm::vec3(10, 0.0, 5);
	glm::vec3 m_CameraFront = glm::vec3(-10.0f, -0.5f, -6.5f);
	glm::vec3 m_CameraUp = glm::vec3(0.0, 1.0, 0.0);
	Window* m_Window;
	float m_DeltaTime = 0.0f;
	float m_LastFrame = 0.0f;
	float m_CurrentFrame = 0.0f;
};