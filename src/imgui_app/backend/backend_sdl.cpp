/**
 * @file    backend_sdl.cpp
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Dear Imgui SDL+OpenGL Backend Class implementation file.
 */

/*****************************************************************************/

/* Libraries */

// Class Header
#include "backend_sdl.h"

// Standard Libraries
#include <iostream>

// Imgui Libraries
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "SDL_opengl.h"

/*****************************************************************************/

/* Construction & Destruction */

// None

/*****************************************************************************/

/* Public Methods */

bool BackendSDL::init(const char* window_title, int window_width,
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

void BackendSDL::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void BackendSDL::poll_events()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        ImGui_ImplSDL2_ProcessEvent(&e);

        if (e.type == SDL_QUIT)
        {   events.push({ AppEventType::QUIT });   }
    }
}

bool BackendSDL::pop_event(AppEvent& event)
{
    if (events.empty())
    {   return false;   }

    event = events.front();
    events.pop();

    return true;
}

void BackendSDL::new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void BackendSDL::render()
{
    ImGui::Render();

    glViewport(0, 0,
        (int)ImGui::GetIO().DisplaySize.x,
        (int)ImGui::GetIO().DisplaySize.y);

    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
    limit_fps();
}

bool BackendSDL::is_vsync_enabled()
{
    return vsync_enabled;
}

/*****************************************************************************/

/* Private Methods */

bool BackendSDL::window_init(const char* title, int width, int height,
    const bool maximized)
{
    // Initialize SDL
    bool fail = false;
    fail |= SDL_Init(SDL_INIT_VIDEO) < 0;
    fail |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0;
    fail |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0) < 0;
    if (fail)
    {
        std::printf("Error: Fail to initialize SDL\n");
        return false;
    }

    // Check if a display is available
    int display = SDL_GetNumVideoDisplays() > 0 ? 0 : -1;
    if (display == -1)
    {
        std::printf("Error: Display screen not found\n");
        return false;
    }

    // Get 75% display resolution for window size if 0 size arguments
    if ( (width == 0) || (height == 0) )
    {
        SDL_DisplayMode dm;
        if (SDL_GetCurrentDisplayMode(display, &dm) == 0)
        {
            width =  (dm.w * 3) / 4; // 3/4 == 0.75
            height = (dm.h * 3) / 4; // 3/4 == 0.75
        }
        else
        {
            width  = 800;
            height = 600;
        }
    }

    // Create Window
    uint32_t window_flags =
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
    if (maximized)
    {   window_flags = window_flags | SDL_WINDOW_MAXIMIZED;   }
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED_DISPLAY(display),
        SDL_WINDOWPOS_CENTERED_DISPLAY(display),
        width, height,
        window_flags
    );
    if (window == NULL)
    {
        std::printf("Error: Fail to create window\n");
        window = nullptr;
        return false;
    }

    // Set minimum window size (note: no all OS support this)
    SDL_SetWindowMinimumSize(window, width, height);

    return true;
}

bool BackendSDL::opengl_init()
{
    // Create OpenGL Context
    gl_context = SDL_GL_CreateContext(window);
    if (gl_context == NULL)
    {
        std::printf("Error: Fail to initialize OpenGL\n");
        return false;
    }

    // Limit FPS to monitor framerate
    vsync_enabled = true;
    SDL_GL_MakeCurrent(window, gl_context);
    if (SDL_GL_SetSwapInterval(-1) < 0)
    {
        if (SDL_GL_SetSwapInterval(1) < 0)
        {
            std::printf("Warning: Fail to limit FPS with V-Sync\n");
            vsync_enabled = false;
        }
    }

    return true;
}

bool BackendSDL::imgui_init() const
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();  // ImGui::StyleColorsLight();

    // Setup DPI Scaling
    ImGuiStyle& style = ImGui::GetStyle();
    float main_scale = ImGui_ImplSDL2_GetContentScaleForDisplay(0);
    style.ScaleAllSizes(main_scale);
    io.ConfigDpiScaleFonts = true;
    io.ConfigDpiScaleViewports = true;

    // Default Font setup
    const float default_font_size = 18.0f;
    ImFontConfig font_cfg;
    font_cfg.SizePixels = default_font_size;
    font_cfg.OversampleH = 3;
    font_cfg.OversampleV = 3;

    // Load Custom Fonts
    #if 1
    #elif 2
    if (!state.font_default)
    {
        state.font_default = io.Fonts->AddFontDefault();
        io.FontDefault = state.font_default;
    }
    #else  // Custom Fonts disabled
    float font_size = 14.0f;
    std::filesystem::path font;
    std::filesystem::path program_dir = getProgramDirectory();
    if (!state.font_default)
    {
        // Default Font
        #if 0 // Custom font disabled
            font = program_dir / "fonts" / "FreeMono.ttf";
            font_size = 18.0f;
            state.font_default =
                io.Fonts->AddFontFromFileTTF(font.string().c_str(), font_size);
        #endif
        if (!state.font_default)
        {
            state.font_default = io.Fonts->AddFontDefault();
        }
        io.FontDefault = state.font_default;
    }
    if (!state.font_h1)
    {
        // Header 1 Font
        font = program_dir / "fonts" / "FreeMono.ttf";
        font_size = 36.0f;
        state.font_h1 =
            io.Fonts->AddFontFromFileTTF(font.string().c_str(), font_size);
    }
    if (!state.font_h2)
    {
        // Header 2 Font
        font = program_dir / "fonts" / "FreeMono.ttf";
        font_size = 32.0f;
        state.font_h2 =
            io.Fonts->AddFontFromFileTTF(font.string().c_str(), font_size);
    }
    if (!state.font_h3)
    {
        // Header 3 Font
        font = program_dir / "fonts" / "FreeMono.ttf";
        font_size = 24.0f;
        state.font_h3 =
            io.Fonts->AddFontFromFileTTF(font.string().c_str(), font_size);
    }
    #endif

    // When viewports are enabled we tweak WindowRounding/WindowBg so
    // platform windows can look identical to regular ones.
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    if (!ImGui_ImplSDL2_InitForOpenGL(window, gl_context))
    {
        std::printf("Error: Fail to initialize Imgui\n");
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 130"))
    {
        std::printf("Error: Fail to use OpenGl with Imgui\n");
        return false;
    }

    return true;
}

void BackendSDL::limit_fps()
{
    // Do nothing if vsync is active
    if (is_vsync_enabled())
    {   return;   }

    static constexpr uint8_t DEFAULT_FPS_LIMIT = 60U;
    static constexpr float frame_limit_time =
        static_cast<float>(1.0F / DEFAULT_FPS_LIMIT);

    static uint64_t t0_frame = SDL_GetPerformanceCounter();
    float frame_time =
        static_cast<float>(SDL_GetPerformanceCounter() - t0_frame) /
        static_cast<float>(SDL_GetPerformanceFrequency());

    if (frame_time < frame_limit_time)
    {   SDL_Delay((uint32_t)((frame_limit_time - frame_time) * 1000.0f));   }

    t0_frame = SDL_GetPerformanceCounter();
}

/*****************************************************************************/
