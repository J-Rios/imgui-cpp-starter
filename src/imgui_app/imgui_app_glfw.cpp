/**
 * @file    imgui_app_glfw.h
 * @author  Jose Miguel Rios Rubio <jrios.github@gmail.com>
 * @date    2025-12-03
 * @version 1.0.0
 * @brief   Dear Imgui main application implementation file (GLFW backed).
 */

/*****************************************************************************/

/* Libraries */

// Header
#include "imgui_app.h"

// Standard Libraries
#include <iostream>
#include <random>

// Imgui Libraries
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

// Auxiliary Libraries
#include "version_info.h"

/*****************************************************************************/

/* Data Types */

/**
 * @brief RGB Color structure.
 */
struct s_color
{
    float red;
    float green;
    float blue;
};

/*****************************************************************************/

/* Function Prototypes */

/**
 * @brief Generate and return a random RGB color.
 * @return s_color Random RGB color structure.
 */
static s_color color_random();

/*****************************************************************************/

/* Main Imgui Function */

int imgui_app()
{
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(
        WINDOW_WIDTH, WINDOW_HEIGHT,
        PROJECT_TITLE,
        nullptr,
        nullptr
    );
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Limit FPS to monitor framerate

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Window");
        ImGui::Text("Running ImGui + GLFW");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        if (ImGui::Button("Press"))
        {
            std::printf("Button Pressed\n");
            s_color bg_color = color_random();
            glClearColor(bg_color.red, bg_color.green, bg_color.blue, 1.0f);
        }
        ImGui::End();

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}


/*****************************************************************************/

/* Auxiliary Functions */

/**
 * @brief Generate and return a random RGB color.
 * @return s_color Random RGB color structure.
 */
static s_color color_random()
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    s_color random_color;
    random_color.red = dist(rng);
    random_color.green = dist(rng);
    random_color.blue = dist(rng);

    return random_color;
}

/*****************************************************************************/
