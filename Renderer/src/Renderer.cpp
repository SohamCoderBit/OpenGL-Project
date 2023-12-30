#include "Renderer.h"
#include "ai_assert.h"
#include "Application.h"


float Vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-1.0f, 0.0f,  1.0f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 2.0f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

unsigned int Indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};


glm::vec3 PyramidPositions[4] = {
	glm::vec3(0.0f , -0.5f , -5.0f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
};

glm::vec3 angles[4] = {
	glm::vec3(0.0f , 0.0f , 0.0f),
	glm::vec3(0.0f , 0.0f , 0.0f),
	glm::vec3(0.0f , 0.0f , 0.0f),
	glm::vec3(0.0f , 0.0f , 0.0f)
};
glm::mat4 Model = glm::mat4(1.0f);
glm::mat4 View = glm::mat4(1.0f);
glm::mat4 Proj = glm::mat4(1.0f);

static bool openDockspace = true;

Renderer::Renderer()
{
	Application& app = Application::Get();
	m_Window = &(app.GetWindow());
}

void Renderer::Init()
{
	shader = CreateScope<Shader>("../Res/Shader/Basic.Shader");

	vertexbuffer = CreateScope<VertexBuffer>();
	indexbuffer = CreateScope<IndexBuffer>();
	vertexArray = CreateScope<VertexArray>();
	framebuffer = CreateScope<FrameBuffers>();

	vertexArray->Bind();

	vertexbuffer->Bind();
	vertexbuffer->AddBufferData(Vertices, sizeof(Vertices));

	indexbuffer->Bind();
	indexbuffer->AddBufferData(Indices, sizeof(Indices));

	Layout.AddLayoutData(GL_FLOAT, 3);
	Layout.AddLayoutData(GL_FLOAT, 3);
	Layout.AddLayoutData(GL_FLOAT, 2);
	vertexArray->AddBuffer(vertexbuffer.get(), Layout);

	vertexArray->UnBind();

	BrickTexture = CreateScope<Texture>("../Res/Texture/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	BrickTexture->TextureUnit(shader.get(), "tex0", 0);
}

void Renderer::Draw()
{

	shader->Bind();
	vertexArray->Bind();
	framebuffer->Bind();

	BrickTexture->Bind();


	Model = glm::mat4(1.0f);
	Proj = glm::mat4(1.0f);

	ImGui::Begin("Demo window");
	ImGui::Button("Hello!");
	for (int i = 0; i < 4; i++)
	{
		std::string Pos = "Position " + std::to_string(i);
		ImGui::SliderFloat3(Pos.c_str(), &(PyramidPositions[i].x), -10.0f, 10.0f);

		std::string AngleLabel = "Angle " + std::to_string(i);
		ImGui::SliderFloat3(AngleLabel.c_str(), &(angles[i].x), -100.0f, 100.0f);
	}
	ImGui::End();

	View = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);

	Proj = glm::perspective(glm::radians(45.0f), (float)(m_Window->m_WindowData.Width)/ (float)(m_Window->m_WindowData.Height), 0.1f, 100.0f);

	unsigned int ViewLocation = shader->GetUniformLocation("view");
	glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(View));

	unsigned int ProjLocation = shader->GetUniformLocation("proj");
	glUniformMatrix4fv(ProjLocation, 1, GL_FALSE, glm::value_ptr(Proj));

	for (int i = 0; i < 4; i++)
	{
		Model = glm::mat4(1.0f);
		Model = glm::translate(View, PyramidPositions[i]);
		Model = glm::rotate(Model, glm::radians(angles[i].x), glm::vec3(1.0f, 0.0f, 0.0f));
		Model = glm::rotate(Model, glm::radians(angles[i].y), glm::vec3(0.0f, 1.0f, 0.0f));
		Model = glm::rotate(Model, glm::radians(angles[i].z), glm::vec3(0.0f, 0.0f, 1.0f));

		unsigned int ModelLocation = shader->GetUniformLocation("model");
		glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));

		glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, 0);
	}
}

//void Renderer::Update()
//{
//
//	glViewport(0, 0, m_Window->m_WindowData.Width, m_Window->m_WindowData.Height);
//	glEnable(GL_DEPTH_TEST);
//
//	glfwSetWindowUserPointer(m_Window->GetOpenGLWindow(), this);
//	//glfwSetKeyCallback(m_Window, KeyInputHandler);
//
//
//	while (!window->WindowShouldClose())
//	{
//		m_CurrentFrame = static_cast<float>(glfwGetTime());
//		m_DeltaTime = m_CurrentFrame - m_LastFrame;
//		m_LastFrame = m_CurrentFrame;
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		this->Draw();
//
//		glfwSwapBuffers(window->GetOpenGLWindow());
//
//		glfwPollEvents();
//
//	}
//
//
//}

//void Renderer::KeyInputHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
//	if (renderer != nullptr)
//	{
//		renderer->HandleKey(key, action);
//	}
//}

//void Renderer::HandleKey(int key, int action)
//{
//	const float cameraSpeed = 10.0f * m_DeltaTime;
//
//	if (action == GLFW_PRESS || action == GLFW_REPEAT)
//	{
//		switch (key)
//		{
//		case GLFW_KEY_ESCAPE:
//			glfwSetWindowShouldClose(m_Window, true);
//			break;
//
//		case GLFW_KEY_W:
//			m_CameraPosition += cameraSpeed * m_CameraFront;
//			std::cout << "W Pressed" << std::endl;
//			break;
//		case GLFW_KEY_S:
//			m_CameraPosition -= cameraSpeed * m_CameraFront;
//			std::cout << "S Pressed" << std::endl;
//			break;
//		case GLFW_KEY_A:
//			m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;
//			std::cout << "A Pressed" << std::endl;
//			break;
//		case GLFW_KEY_D:
//			m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;
//			std::cout << "D Pressed" << std::endl;
//			break;
//		}
//	}
//}
