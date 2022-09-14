#pragma once

#include <imgui.h>

#include "Window.h"

namespace NImguiLayer
{
	class ImguiLayer
	{
		int winWidth, winHeight;
		int display_w, display_h;

	public:
		void init(GLFWwindow* window);
		void run(GLFWwindow* window, bool show_demo_window, ImGuiIO& io);
		void destroy();
	};

}