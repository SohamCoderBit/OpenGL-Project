#pragma once
#include <iostream>

#include "OpenGL.h"
#include "Renderer.h"

class Window
{
public:
	uint32_t Height = 0, Width = 0;
	Window(uint32_t height , uint32_t width);
	~Window();
	void Init();
	void ShutDown();
private:
	Window(const Window&);
	Window& operator=(const Window&);

private:
	GLFWwindow* m_Window;
};