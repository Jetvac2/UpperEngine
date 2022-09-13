
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

#include "imguiLayer.h"
#include "Window.h"


namespace NImguiLayer
{
	void ImguiLayer::init(GLFWwindow* window)
	{
        //Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        

        const char* glsl_version = "#version 150";

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);  
	}

    void ImguiLayer::run(GLFWwindow* window, bool show_demo_window, ImGuiIO& io)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        io.DisplaySize = ImVec2(width, height);

        if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Begin("Hello, world!");

        ImGui::Text("This is some useful text.");
        ImGui::Checkbox("Demo Window", &show_demo_window);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImguiLayer::destroy()
    {
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
