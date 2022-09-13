#pragma once

#include <imgui.h>

#include "Window.h"

namespace NImguiLayer
{
	class ImguiLayer
	{
	public:
		void init(GLFWwindow* window);
		void run(GLFWwindow* window, bool show_demo_window, ImGuiIO& io);
		void destroy();
	};
}