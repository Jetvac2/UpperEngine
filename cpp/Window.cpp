#include <GLFW/glfw3.h>

#include "Window.h"
#include "imguiLayer.h"

namespace NWindow
{
    int Window::run(GLFWwindow* window)
    {
        /* Initialize the library */
        if (!glfwInit())
            return -1;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(720, 480, "UpperEngine", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);
        glClearColor(1, 0, 0, 1);

        glfwSwapInterval(1);

        NImguiLayer::ImguiLayer imguiLayer = NImguiLayer::ImguiLayer();

        imguiLayer.init(window);
        ImGuiIO& io = ImGui::GetIO();
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Poll for and process events */
            glfwPollEvents();

            glClear(GL_COLOR_BUFFER_BIT);

            /* Render here */
            imguiLayer.run(window, true, io);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
        }

        imguiLayer.destroy();
        glfwTerminate();

        return 0;
    }
}
