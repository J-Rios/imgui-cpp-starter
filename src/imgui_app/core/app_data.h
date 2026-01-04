/**
 * @file    app_data.h
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Application context and state data definition file.
 * @details
 * The Application context contains global configurations, resources and
 * references that are created and setup during application startup.
 *
 * The Application state contains different data that changes during runtime
 * and is normally check/set by the UI and the application logic.
 */

/*****************************************************************************/

/* Include Guard */

#pragma once

/*****************************************************************************/

/* Libraries */

// Standard Libraries
#include <string>

// Class Interfaces
#include "backend_interface.h"
#include "ui_interface.h"

// Imgui Libraries
#include "imgui.h"

// Auxiliary Libraries
#include "project_info.h"

/*****************************************************************************/

/* Application Context Data */

/**
 * @brief Application Context data.
 */
struct AppContext
{
    const s_project_info* project_info;
    std::unique_ptr<IBackend> backend;
    ImGuiIO* io = nullptr;
    ImGuiStyle* style = nullptr;
    IUI* ui = nullptr;
};

/*****************************************************************************/

/* Application State Data */

/**
 * @brief Application State data.
 */
struct AppState
{
    /* Data Types */

    enum class e_theme : uint32_t { DARK, LIGHT, CLASSIC, CUSTOM, NUM_THEMES };
    static constexpr uint32_t NUM_THEMES =
        static_cast<uint32_t>(e_theme::NUM_THEMES);

    /***************************/

    /* UI */

    // UI: Constants (layout)
    static constexpr float footbar_height = 24.0f;
    const ImVec4 color_footbar_bg{0.13f, 0.47f, 0.82f, 1.0f};

    // UI: Data
    int window_width = 0;
    int window_height = 0;
    e_theme theme = e_theme::DARK;
    std::string str_theme = "Undefined";
    std::string footbar_project_info = "Undefined";
    ImFont* font_default = nullptr;
    ImFont* font_h1 = nullptr;
    ImFont* font_h2 = nullptr;
    ImFont* font_h3 = nullptr;

    /***************************/

    /* Internal Logic */

    // Logic: Constants
    // ...

    // Logic: Requests
    bool connect_requested = false;
    bool disconnect_requested = false;
    bool exit_request = false;
    bool show_exit_popup = false;

    // Logic: State
    bool running = true;
    bool vsync_enabled = false;
    float fps = 0.0f;
    std::string status = "Ready";

    // Logic: Data
    // ...

    void update()
    {
        switch (theme)
        {
            case e_theme::DARK:    str_theme = "Dark";      break;
            case e_theme::LIGHT:   str_theme = "Light";     break;
            case e_theme::CLASSIC: str_theme = "Classic";   break;
            case e_theme::CUSTOM:  str_theme = "Custom";    break;
            default:               str_theme = "Undefined"; break;
        }

        if (connect_requested)
        {
            status = "Connected";
            connect_requested = false;
        }

        if (disconnect_requested)
        {
            status = "Disconnected";
            disconnect_requested = false;
        }
    }
};

/*****************************************************************************/
