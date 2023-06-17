#include <iostream>

#include "Window.h"

int main()
{
	Window* m_window = nullptr;
		
	glfwInit();

	if (!glfwInit())
	{
		glfwTerminate();
	}

	m_window = new Window(800, 800);


	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW LOAD ERROR" << std::endl;
	}

	m_window->Init();

	delete m_window;

	glfwTerminate();

}