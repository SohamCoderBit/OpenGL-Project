#pragma once

#include "OpenGL.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"


class ImGuiLayer 
{
public :
	ImGuiLayer();
	void Init();
	void BeginFrame();
	void EndFrame();
	void ShutDown();
};