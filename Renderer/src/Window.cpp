#include "Window.h"

Window::Window(uint32_t height, uint32_t width):Height(height) , Width(width)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(Height, Width, "OpenGL Renderer", nullptr, nullptr);

	if (!m_Window)
	{
		glfwTerminate();
		std::cout << "Window Can Not Be Created" << std::endl;
	}


	glfwMakeContextCurrent(m_Window);


}

Window::~Window()
{
	ShutDown();
}


void Window::Init()
{
	Renderer* m_Renderer = new Renderer();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init();
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(m_Window))
	{
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_Renderer->Draw();

		glfwSwapBuffers(m_Window);

		glfwPollEvents();

		
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	delete m_Renderer;
}

void Window::ShutDown()
{
	glfwDestroyWindow(m_Window);
}

