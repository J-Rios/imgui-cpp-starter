/**
 * @file    backend_glfw.cpp
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Dear Imgui GLFW+OpenGL Backend Class implementation file.
 */

/*****************************************************************************/

/* Libraries */

// Class Header
#include "backend_glfw.h"

// Standard Libraries
#include <iostream>

// Imgui Libraries
#include "imgui.h"
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

/*****************************************************************************/

/* Construction & Destruction */

// None

/*****************************************************************************/

/* GLFW Error Callback */

static void glfw_error_callback(int error, const char* description)
{
    std::printf("GLFW Error %d: %s\n", error, description);
}

/*****************************************************************************/

/* Public Methods */

bool BackendGLFW::init(const char* window_title, int window_width,
    int window_height, const bool window_maximized)
{
    // SDL init and Main Window creation
    if (window_init(window_title, window_width, window_height,
                    window_maximized) == false)
    {   return false;   }

    // OpenGL init
    if (opengl_init() == false)
    {   return false;   }

    // Imgui init
    if (imgui_init() == false)
    {   return false;   }

    return true;
}

void BackendGLFW::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void BackendGLFW::poll_events()
{
    glfwPollEvents();

    if (glfwWindowShouldClose(window))
    {   events.push({ AppEventType::QUIT });   }
}

bool BackendGLFW::pop_event(AppEvent& event)
{
    if (events.empty())
    {   return false;   }

    event = events.front();
    events.pop();

    return true;
}

void BackendGLFW::new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
}

void BackendGLFW::render()
{
    ImGui::Render();

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
}

/*****************************************************************************/

/* Private Methods */


bool BackendGLFW::window_init(const char* title, int width, int height,
    const bool maximized)
{
    // Initialize GLFW
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        std::printf("Error: Fail to initialize SDL\n");
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Get primary monitor
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor)
    {
        std::printf("Error: Display screen not found\n");
        glfwTerminate();
        return false;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode)
    {
        std::printf("Error: Failed to get video mode\n");
        glfwTerminate();
        return false;
    }

    // Get 75% display resolution for window size if 0 size arguments
    if (width == 0 || height == 0)
    {
        width  = (mode->width  * 3) / 4;
        height = (mode->height * 3) / 4;
    }

    // Create Window
    window = glfwCreateWindow(
        width,
        height,
        title,
        maximized ? monitor : nullptr,
        nullptr
    );
    if (!window)
    {
        std::printf("Error: Fail to create window\n");
        glfwTerminate();
        return false;
    }

    // Center window if not fullscreen
    if (!maximized)
    {
        int xpos = (mode->width  - width)  / 2;
        int ypos = (mode->height - height) / 2;
        glfwSetWindowPos(window, xpos, ypos);
    }

    // Set minimum window size (note: no all OS support this)
    glfwSetWindowSizeLimits(window, width, height,
        GLFW_DONT_CARE, GLFW_DONT_CARE);

    // Make context current
    glfwMakeContextCurrent(window);

    // Enable vsync by default
    glfwSwapInterval(1);
    vsync_enabled = true;

    return true;
}

bool BackendGLFW::opengl_init()
{
    // Load OpenGL via glad
    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::printf("Error: Fail to initialize OpenGL\n");
        return false;
    }

    return true;
}

bool BackendGLFW::imgui_init() const
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Fix GLFW UI sizes
    int fb_w, fb_h;
    int win_w, win_h;
    glfwGetFramebufferSize(window, &fb_w, &fb_h);
    glfwGetWindowSize(window, &win_w, &win_h);
    io.DisplaySize = ImVec2((float)win_w, (float)win_h);
    io.DisplayFramebufferScale = ImVec2(
        static_cast<float>(fb_w / win_w),
        static_cast<float>(fb_h / win_h)
    );

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();  // ImGui::StyleColorsLight();

    // Setup DPI Scaling
    ImGuiStyle& style = ImGui::GetStyle();
    float xscale = 1.0f, yscale = 1.0f;
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (monitor)
    {   glfwGetMonitorContentScale(monitor, &xscale, &yscale);   }
    const float main_scale = xscale;
    style.ScaleAllSizes(main_scale);
    io.ConfigDpiScaleFonts     = true;
    io.ConfigDpiScaleViewports = true;

    // Default Font setup
    const float default_font_size = 18.0f * main_scale;
    ImFontConfig font_cfg;
    font_cfg.SizePixels = default_font_size;
    font_cfg.OversampleH = 3;
    font_cfg.OversampleV = 3;

    // Load Custom Fonts
#if 1
#elif 2
    if (!state.font_default)
    {
        state.font_default = io.Fonts->AddFontDefault(&font_cfg);
        io.FontDefault = state.font_default;
    }
#else  // Custom Fonts disabled
    if (!state.font_default)
    {
        state.font_default =
            io.Fonts->AddFontFromFileTTF(
                "fonts/FreeMono.ttf",
                18.0f * main_scale,
                &font_cfg
            );
        if (!state.font_default)
            state.font_default = io.Fonts->AddFontDefault(&font_cfg);

        io.FontDefault = state.font_default;
    }
#endif

    // Viewports tweaks
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Init ImGui GLFW+OpenGL backend
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
    {
        std::printf("Error: Fail to initialize ImGui GLFW\n");
        return false;
    }
    if (!ImGui_ImplOpenGL3_Init("#version 130"))
    {
        std::printf("Error: Fail to initialize ImGui OpenGL\n");
        return false;
    }

    return true;
}

/*****************************************************************************/
