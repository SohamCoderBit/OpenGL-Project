#include <iostream>

#include "Renderer.h"
#include "Application.h"

Application Application::s_Instance;

Application::Application()
{
	m_Window = CreateScope<Window>(WindowData());
	m_Renderer = CreateScope<Renderer>();
	m_ImGuiContext = CreateScope<ImGuiLayer>();

	glViewport(0, 0, m_Window->m_WindowData.Width, m_Window->m_WindowData.Height);
	glEnable(GL_DEPTH_TEST);

	m_Renderer->Init();
	m_ImGuiContext->Init();
}

void Application::Run()
{

	while (m_Running)
	{
		m_ImGuiContext->BeginFrame();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_Renderer->Draw();

		m_ImGuiContext->EndFrame();

		m_Window->onUpdate();

		m_Running = !(m_Window->WindowShouldClose());
	}
}
