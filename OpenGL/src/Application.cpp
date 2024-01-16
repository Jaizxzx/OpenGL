#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui-v1.6\imgui.h"
#include "imgui-v1.6\imgui_impl_glfw_gl3.h"
#include "tests\TestClearColor.h"
#include "tests\TestTexture2D.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glewInit();

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Graphic Test Pipeline", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(2);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error" << std::endl;
    }
    std::cout << glGetString(GL_VERSION)<< " Is the current opengl version." << std::endl;
    {
        /*
        float positions[] = {
            -50.5f, -50.5f, 0.0f, 0.0f,
             50.5f, -50.5f, 1.0f, 0.0f, 
             50.5f,  50.5f, 1.0f, 1.0f,
            -50.5f,  50.5f, 0.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0  // Fix: Change the first index of the second triangle to 3
        };
        */
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        /*
        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        // Create and bind the Index Buffer Object (IBO)
        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3( 0, 0, 0));
        

        Shader shader("res/shaders/Basic.shader"); 
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        Texture texture("res/texture/tiger.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();
        */
        Renderer renderer;
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark(); 

        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>(" 2D Texture ");

        /*
        glm::vec3 translationA(200, 200, 0);
        glm::vec3 translationB(400, 200, 0);


        float r = 0.0f;
        float increment = 0.05f;
        */
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();
            if (currentTest) 
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }
            /*
            {

                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);

            }
            {

                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);

            }
            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;
            r += increment;

            {
               
                ImGui::SliderFloat3("Translate A", &translationA.x, 0.0f, 960.0f);        // Edit 1 float using a slider from 0.0f to 1.0f  
                ImGui::SliderFloat3("Translate B", &translationB.x, 0.0f, 960.0f);        // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }
            */
            ImGui::Render();            
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        delete currentTest;
        if (currentTest != testMenu)
            delete testMenu;
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}