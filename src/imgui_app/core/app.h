/**
 * @file    app.h
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Application main class definition file.
 * @details This component shall contains the application logic.
 * @note    Don't mix app logic and UI, any UI related code shall be added to
 *          "ui" components.
 */

/*****************************************************************************/

/* Include Guard */

#pragma once

/*****************************************************************************/

/* Libraries */

// Standard Libraries
#include <memory>

// Auxiliary Headers
#include "app_data.h"
#include "project_info.h"

/*****************************************************************************/

/* Application Orchestrator */

/**
 * @brief Application Main Class.
 */
class App
{
    /*************************************************************************/

    /* Public Methods */

    public:

    /**
     * @brief Construct a new App object.
     * @param app_name Name to give for this Application.
     */
    App(const s_project_info& project_information);

    /**
     * @brief Run the Application.
     * @return int Application execution finish return code.
     */
    int run();

    /*************************************************************************/

    /* Private Attributes */

    private:

    /**
     * @brief Application Context Data.
     */
    AppContext context;

    /**
     * @brief Application State Data.
     */
    AppState state;

    /*************************************************************************/

    /* Private Methods */

    private:

    /**
     * @brief Initial configuration of the UI.
     */
    void setup_ui();

    /**
     * @brief Draw and render a new frame of the UI.
     */
    void draw_ui();

    /**
     * @brief Close the UI and all it elements.
     */
    void close_ui();

    /**
     * @brief Check and handle events.
     */
    void handle_events();

    /**
     * @brief Update Application data.
     */
    void data_update();

    /**
     * @brief Run application internal logic behaviour.
     */
    void behaviour();
};

/*****************************************************************************/
