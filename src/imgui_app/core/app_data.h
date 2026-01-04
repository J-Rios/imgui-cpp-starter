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
    IUI* ui = nullptr;
};

/*****************************************************************************/

/* Application State Data */

/**
 * @brief Application State data.
 */
struct AppState
{
    bool running = true;
    bool connect_requested = false;
    bool disconnect_requested = false;

    std::string status = "Ready";

    void update()
    {
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
