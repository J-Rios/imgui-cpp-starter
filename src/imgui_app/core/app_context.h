/**
 * @file    app_context.h
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Application context data definition file.
 * @details The Application context contains the different application data
 *          that can be check by the UI and be set by the application logic.
 */

/*****************************************************************************/

/* Include Guard */

#pragma once

/*****************************************************************************/

/* Libraries */

// Standard Libraries
#include <string>

/*****************************************************************************/

/* Application Context */

/**
 * @brief Application Context data.
 */
struct AppContext
{
    bool running = true;

    // Ejemplo de estado
    bool connect_requested = false;
    bool disconnect_requested = false;

    std::string status = "Ready";

    void update_logic()
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
