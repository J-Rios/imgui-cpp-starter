/**
 * @file    backend_sdl.h
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Dear Imgui SDL+OpenGL Backend Class definition file.
 */

/*****************************************************************************/

/* Include Guard */

#pragma once

/*****************************************************************************/

/* Libraries */

// Backend Interface
#include "backend_interface.h"

// Standard Libraries
#include <queue>

// SDL Libraries
#include "SDL.h"

/*****************************************************************************/

/* Imgui SDL Backend */

/**
 * @brief Imgui SDL Backend.
 */
class BackendSDL : public IBackend
{
    /*************************************************************************/

    /* Public Methods */

    public:

    /**
     * @brief Initialize the Imgui Backend and create the GUI window.
     * @param window_title GUI window title.
     * @param window_width GUI Window width.
     * @param window_height GUI Window height.
     * @param window_maximized GUI window creation maximized.
     * @return true Initialization success.
     * @return false Initialization fail.
     */
    bool init(const char* window_title, int window_width=0,
        int window_height=0, const bool window_maximized=false) override;

    /**
     * @brief Close all Imgui Backend related components.
     */
    void shutdown() override;

    /**
     * @brief Backend events handler (check and store events into event queue).
     */
    void poll_events() override;

    /**
     * @brief Get a previous received event.
     * @param event Reference to event received.
     * @return true Received event available.
     * @return false None received event.
     */
    bool pop_event(AppEvent& event) override;

    /**
     * @brief Start a new frame to draw.
     */
    void new_frame() override;

    /**
     * @brief Render the drawn graphics.
     */
    void render() override;

    /**
     * @brief Check if V-Sync is enabled.
     * @return true V-Sync is enabled.
     * @return false V-Sync is disabled.
     */
    bool is_vsync_enabled() override;

    /*************************************************************************/

    /* Private Methods */

    private:

    /**
     * @brief Initialize SDL and Create the Main Window.
     * @param title Window title.
     * @param width Window width.
     * @param height Window height.
     * @param maximized Start window maximized.
     * @param min_width Minimum window width (not always supported).
     * @param min_height Minimum window width (not always supported).
     * @return true Initialization success.
     * @return false Initialization fail.
     */
    bool window_init(const char* title, int width=0, int height=0,
        const bool maximized=false, const int min_width=360,
        const int min_height=240);

    /**
     * @brief Initialize OpenGL.
     * @return true Initialization success.
     * @return false Initialization fail.
     */
    bool opengl_init();

    /**
     * @brief Initialize Imgui.
     * @return true Initialization success.
     * @return false Initialization fail.
     */
    bool imgui_init() const;

    /**
     * @brief Limit Framerate to 60 FPSs.
     * @note Use this when V-Sync is not enabled and you want to limit the
     * FPS to a safe value.
     */
    void limit_fps();

    /*************************************************************************/

    /* Private Attributes */

    private:

    /**
     * @brief GUI window.
     */
    SDL_Window* window = nullptr;

    /**
     * @brief OpenGL Context.
     */
    SDL_GLContext gl_context = nullptr;

    /**
     * @brief Internal queue to store received events.
     */
    std::queue<AppEvent> events;

    /**
     * @brief V-Sync enabled/disabled state.
     */
    bool vsync_enabled = false;
};

/*****************************************************************************/
