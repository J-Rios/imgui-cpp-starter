/**
 * @file    backend_interface.h
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Dear Imgui Backend class interface file.
 * @details This interface shall be used to define-implement any UI Backend.
 */

/*****************************************************************************/

/* Include Guard */

#pragma once

/*****************************************************************************/

/* Libraries */

// Standard Libraries
#include <memory>

// Auxiliary Headers
#include "app_events.h"

/*****************************************************************************/

/* Imgui Backend Interface */

/**
 * @brief Imgui Backend Interface.
 */
struct IBackend
{
    /**
     * @brief Initialize the Imgui Backend and create the GUI window.
     * @param window_title GUI window title.
     * @param window_width GUI Window width.
     * @param window_height GUI Window height.
     * @param window_maximized GUI window creation maximized.
     * @return true Initialization success.
     * @return false Initialization fail.
     */
    virtual bool init(const char* window_title, int window_width=0,
        int window_height=0, const bool window_maximized=false) = 0;

    virtual void shutdown() = 0;

    virtual void poll_events() = 0;
    virtual bool pop_event(AppEvent& event) = 0;

    virtual void new_frame() = 0;
    virtual void render() = 0;
};

/*****************************************************************************/
