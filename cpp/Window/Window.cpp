#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include "imguiLayer.h"

#include"Rendering/VAO.h"
#include"Rendering/shaderClass.h"
#include"Rendering/VBO.h"
#include"Rendering/EBO.h"

// Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};


// Indices for vertices order
GLuint indices[] =
{
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1 // Upper triangle
};


namespace NWindow
{
    //Testing git hub
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
        imguiLayer.init(window);

        ImGuiIO& io = ImGui::GetIO();

        // Generates Shader object using shaders defualt.vert and default.frag
        Shader shaderProgram("includes/Rendering/default.vert", "includes/Rendering/default.frag");



        // Generates Vertex Array Object and binds it
        VAO VAO1;
        VAO1.Bind();

        //Generates Vertex Buffer Object and links it to vertices
        VBO VBO1(vertices, sizeof(vertices));
        // Generates Element Buffer Object and links it to indices
        EBO EBO1(indices, sizeof(indices));

        // Links VBO to VAO
       VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	   VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        //Unbind all to prevent accidentally modifying them
        VAO1.Unbind();
        VBO1.Unbind();
        EBO1.Unbind();

        GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Poll for and process events */
            glfwPollEvents();

            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            /*Render here */
            //Tell OpenGL which Shader Program we want to use
		    shaderProgram.Activate();
            glUniform1f(uniID, 1.5f);
		    // Bind the VAO so OpenGL knows to use it
		    VAO1.Bind();
		    // Draw primitives, number of indices, datatype of indices, index of indices
		    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

            imguiLayer.run(window, true, io);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
        }

        VAO1.Delete();
        VBO1.Delete();
        EBO1.Delete();
        shaderProgram.Delete();

        imguiLayer.destroy();
        glfwTerminate();

        return 0;
    }
}