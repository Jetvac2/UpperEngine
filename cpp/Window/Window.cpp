#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include "imguiLayer.h"
#include "Renderer.h"


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

        gladLoadGL();


        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        glfwSwapInterval(1);

        NImguiLayer::ImguiLayer imguiLayer = NImguiLayer::ImguiLayer();
        NRenderer::Renderer renderer = NRenderer::Renderer();
        imguiLayer.init(window);

        renderer.init();

        ImGuiIO& io = ImGui::GetIO();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Poll for and process events */
            glfwPollEvents();

            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            renderer.run();


            /* Render here */
            imguiLayer.run(window, true, io);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
        }

        
        renderer.destroy();
        imguiLayer.destroy();
        glfwTerminate();

        return 0;
    }
}
