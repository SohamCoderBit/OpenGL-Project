#pragma once
#include <string>
#include <memory>

#include "Renderer.h"
#include "Window.h"
#include "Base.h"
#include "ImGuiLayer.h"




class Application
{
public:
	static Application& Get() { return s_Instance;}
	void Run();
	Window& GetWindow() { return *m_Window; }

private :
	Application();
	Application(const Application&) = delete;
	Application(const Application&&) = delete;

private :
	Scope<Window> m_Window;
	Scope<Renderer> m_Renderer;
	Scope<ImGuiLayer> m_ImGuiContext;
	bool m_Running = true;

private:
	static Application s_Instance;
};
