/**
 * @file    app.cpp
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Application main orchestrator class implementation file.
 * @details This component shall contains the application logic.
 * @note    Don't mix app logic and UI, any UI related code shall be added to
 *          "ui" components.
 */

/*****************************************************************************/

/* Libraries */

// Class Header
#include "app.h"

// Imgui Libraries
#include "imgui.h"
#include "imgui_backend.h"

/*****************************************************************************/

/* Public Methods */

App::App(const s_project_info& project_information)
{
    extern IUI* CreateMainUI(AppContext& app_context, AppState& app_state);

    context.project_info = &project_information;
    context.backend = std::make_unique<IMGUI_BACKEND>();
    context.ui = CreateMainUI(context, state);
}

int App::run()
{
    setup_ui();

    while (state.running)
    {
        state.update();
        handle_events();
        draw_ui();
    }

    close_ui();

    return 0;
}

/*****************************************************************************/

/* Private Methods - UI */

void App::setup_ui()
{
    context.backend->init(context.project_info->PROJECT_NAME);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
}

void App::draw_ui()
{
    context.backend->new_frame();
    ImGui::NewFrame();
    context.ui->draw();
    context.backend->render();
}

void App::close_ui()
{
    context.backend->shutdown();
    ImGui::DestroyContext();
}

/*****************************************************************************/

/* Private Methods - Handle Events */

void App::handle_events()
{
    context.backend->poll_events();

    AppEvent ev;
    while (context.backend->pop_event(ev))
    {
        if (ev.type == AppEventType::QUIT)
        {   state.running = false;   }
    }
}

/*****************************************************************************/
