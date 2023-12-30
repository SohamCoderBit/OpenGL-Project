#include "Window.h"

Window::Window(const WindowData& windowData)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Init(windowData);
}

void Window::Init(const WindowData& windowData)
{
	m_WindowData.Title = windowData.Title;
	m_WindowData.Height= windowData.Height;
	m_WindowData.Width = windowData.Width;


	int succes = glfwInit();
	if (!succes)
	{
		std::cout << "GLFW Has Not Intialized " << std::endl;
		glfwTerminate();
	}

	m_Window = glfwCreateWindow(m_WindowData.Width, m_WindowData.Width, m_WindowData.Title.c_str(), nullptr, nullptr);

	if (!m_Window)
	{
		glfwTerminate();
		std::cout << "Window Can Not Be Created" << std::endl;
	}	

	glfwMakeContextCurrent(m_Window);


	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW LOAD ERROR" << std::endl;
	}

}

Window::~Window()
{
	ShutDown();
}


void Window::ShutDown()
{
	glfwDestroyWindow(m_Window);
}

void Window::onUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

