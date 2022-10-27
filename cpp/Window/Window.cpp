#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include "imguiLayer.h"

#include "Rendering/stb_image.h"
#include "Rendering/Texture.h"
#include"Rendering/VAO.h"
#include"Rendering/shaderClass.h"
#include"Rendering/VBO.h"
#include"Rendering/EBO.h"


// Vertices coordinates
GLfloat vertices[] =
{ //  COORDINATES              /     COLORS         Tex Coords   //
    -0.5f, -0.5f,  0.0f,     1.0f, 0.3f,  0.0f,     0.0f, 0.0f,// Lower left corner
    -0.5f,  0.5f,  0.0f,     0.0f, 1.0f,  0.0f,     0.0f, 1.0f,// Lower right corner
     0.5f,  0.5f,  0.0f,     0.0f, 0.0f,  1.0f,     1.0f, 1.0f,// Upper corner
     0.5f, -0.5f,  0.0f,     1.0f, 1.0f,  1.0f,     1.0f, 0.0f// Inner left    
};


// Indices for vertices order
GLuint indices[] =
{
    0, 2, 1,
    0, 3, 2
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
       VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	   VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	   VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

        //Unbind all to prevent accidentally modifying them
        VAO1.Unbind();
        VBO1.Unbind();
        EBO1.Unbind();

        GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

        // Textures
        
        Texture testText("ResourceFiles/Textures/textureTest.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
        testText.texUnit(shaderProgram, "tex0", 0);

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
            
            testText.Bind();
		    // Bind the VAO so OpenGL knows to use it
		    VAO1.Bind();
		    // Draw primitives, number of indices, datatype of indices, index of indices
		    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            imguiLayer.run(window, true, io);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
        }

        VAO1.Delete();
        VBO1.Delete();
        EBO1.Delete();
        testText.Delete();

        shaderProgram.Delete();

        imguiLayer.destroy();
        glfwTerminate();

        return 0;
    }
}