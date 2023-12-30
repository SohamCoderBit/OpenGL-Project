#pragma once
#include <iostream>

#include "OpenGL.h"


struct WindowData
{
	std::string Title;
	uint32_t Height, Width;
	WindowData(const std::string& title = "OpenGl Renderer", uint32_t height = 1080, uint32_t width = 1920) : Title(title), Height(height), Width(width) {}
};


class Window
{
public:
	Window();
	Window(const WindowData& windowData);
	~Window();
	void ShutDown();
	void onUpdate();
	void* GetOpenGLWindow() { return m_Window; }
	int WindowShouldClose() 
	{
		if (m_Window != nullptr)
		{
			return glfwWindowShouldClose(m_Window);
		}
		return 0;
	}
public :
	WindowData m_WindowData;
	
private:
	Window(const Window&);
	Window& operator=(const Window&);
	void Init(const WindowData& windowData);

private:
	GLFWwindow* m_Window;
};