#pragma once

#include <GLFW/glfw3.h>

namespace NWindow
{
	class Window
	{
	public:
		GLFWwindow* win;
		int run(GLFWwindow* window);
	};
}




