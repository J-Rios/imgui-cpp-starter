/**
 * @file    ui_main.cpp
 * @date    2026-01-01
 * @version 1.0.0
 * @brief   Main UI implementation file.
 * @details This component defines the application main UI to be shown.
 * @note    Don't mix app logic and UI, any app logic related code shall be
 *          added to the "core" components.
 */

/*****************************************************************************/

/* Libraries */

// Class Header
#include "ui_main.h"

// Standard Libraries
// ...

// Imgui Libraries
#include "imgui.h"

/*****************************************************************************/

/* Fonts Data */

// Notes:
// - These font data comes from linked fonts library (at CMake)
// - You can check the symbol names of .o files via "nm build/fonts/font.o"

// Free Monospace Font
extern "C" { extern const unsigned char _binary_FreeMono_ttf_start[]; }
extern "C" { extern const unsigned char _binary_FreeMono_ttf_end[]; }
inline const uint8_t* FONT_FREEMONO = _binary_FreeMono_ttf_start;
inline const size_t FONT_FREEMONO_SIZE =
    static_cast<size_t>(_binary_FreeMono_ttf_end - _binary_FreeMono_ttf_start);

/*****************************************************************************/

/* Factory Simple */

IUI* CreateMainUI(AppContext& app_context, AppState& app_state)
{
    static MainUI ui(app_context, app_state);
    return &ui;
}

/*****************************************************************************/

/* Public Methods */

void MainUI::setup()
{
    context.io = &(ImGui::GetIO());
    context.style = &(ImGui::GetStyle());

    // context.io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // context.io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // context.io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Default Font setup
    const float default_font_size = 18.0f;
    ImFontConfig font_cfg;
    font_cfg.SizePixels = default_font_size;
    font_cfg.OversampleH = 3;
    font_cfg.OversampleV = 3;
    if (!state.font_default)
    {
        state.font_default = context.io->Fonts->AddFontDefault();
        context.io->FontDefault = state.font_default;
    }

    // Load Custom Fonts
    if (!state.font_h1)
    {   state.font_h1 = add_font(FONT_FREEMONO, FONT_FREEMONO_SIZE, 32.0f);   }
    if (!state.font_h2)
    {   state.font_h2 = add_font(FONT_FREEMONO, FONT_FREEMONO_SIZE, 24.0f);   }
    if (!state.font_h3)
    {   state.font_h3 = add_font(FONT_FREEMONO, FONT_FREEMONO_SIZE, 18.0f);   }
    if(!state.font_text)
    {
        state.font_text = add_font(FONT_FREEMONO, FONT_FREEMONO_SIZE, 14.0f);
    }

    // When viewports are enabled we tweak WindowRounding/WindowBg so
    // platform windows can look identical to regular ones.
    if (context.io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        context.style->WindowRounding = 0.0f;
        context.style->Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
}

void MainUI::draw()
{
    /* Main UI Window */

    // Get current FPS
    state.fps = ImGui::GetIO().Framerate;

    // Get current used Imgui style
    context.style = &(ImGui::GetStyle());

    ImGui::PushFont(state.font_text);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(context.io->DisplaySize);
    ImGui::Begin("Main", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_MenuBar
    );

    // Window Menu Bar
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit", "Alt+F4"))
            {   state.exit_request = true;   }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
            {   state.about_request = true;   }
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    // Get current Imgui main window size
    state.full_window_width = static_cast<int>(ImGui::GetIO().DisplaySize.x);
    state.full_window_height = static_cast<int>(ImGui::GetIO().DisplaySize.y);
    state.window_width = static_cast<int>(ImGui::GetContentRegionAvail().x);
    state.window_height = static_cast<int>(ImGui::GetContentRegionAvail().y);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::BeginGroup();
        float content_height =
            static_cast<float>(state.window_height) - state.footbar_height;
        ImGui::BeginChild("ContentArea", ImVec2(0, content_height));
            draw_content();
        ImGui::EndChild();
        draw_footbar();
    ImGui::EndGroup();
    draw_exit_popup();

    ImGui::PopStyleVar();
    ImGui::End();
    ImGui::PopFont();
}

/*****************************************************************************/

/* Private Methods - Setup */

ImFont* MainUI::add_font(const uint8_t* data, const size_t data_len,
    const float size)
{
    void* ptr_data = const_cast<void*>(static_cast<const void*>(data));
    int _data_len = static_cast<int>(data_len);
    return context.io->Fonts->AddFontFromMemoryTTF(ptr_data, _data_len, size);
}

/*****************************************************************************/

/* Private Methods - Draw Content */

void MainUI::draw_content()
{
    static constexpr float margin_x = 24.0f;
    static constexpr float margin_y = 16.0f;
    float spacing = (ImGui::GetStyle().ItemSpacing.x * 2.0f);

    // New Region (child)
    ImGui::BeginChild("Content", ImVec2(0, 0), false);

    // Apply Margin
    ImGui::Dummy(ImVec2(0.0f, margin_y));
    ImGui::Indent(margin_x);

    /***********************/

    // Text: Title
    ImGui::PushFont(state.font_h2);
    ImGui::Text("ImGui C++ Starter");
    ImGui::PopFont();

    // Separator
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 10));

    // Button: Connect
    if (ImGui::Button("Connect"))
    {   state.connect_requested = true;   }

    // Button: Disconnect
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::Button("Disconnect"))
    {   state.disconnect_requested = true;   }

    // Text: Status
    ImGui::Text("Status: %s", state.status.c_str());

    // Separator
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 10));

    // Button: Change Theme
    if (ImGui::Button("Change Theme"))
    {   change_theme();   }

    // Text: UI Theme
    ImGui::Text("UI Theme: %s", state.str_theme.c_str());

    // Separator
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 10));

    // Text: Window Width & Heigth
    ImGui::Text("Window Size: %d x %d",
        state.full_window_width, state.full_window_height);

    // Separator
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 10));

    // Text: Framerate
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    // Separator
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 10));

    // Button: Exit
    if (ImGui::Button("Exit"))
    {   state.exit_request = true;   }

    /***********************/

    ImGui::Unindent(margin_x);
    ImGui::EndChild();
}

/*****************************************************************************/

/* Private Methods - Draw Footbar */

void MainUI::draw_footbar()
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, state.color_footbar_bg);
    ImGui::BeginChild("footbar",
        ImVec2(0, state.footbar_height),
        false,
        ImGuiWindowFlags_NoScrollbar);

    float pad = 10.0f;
    float y = ImGui::GetCursorPosY() + 2.5f;
    float w = ImGui::GetWindowWidth();

    // Text: Status
    ImGui::SetCursorPos(ImVec2(pad, y));
    ImGui::Text("Status: %s", state.status.c_str());

    // Text: Project Info
    state.footbar_right_text =
        std::string(context.project_info->PROJECT_VERSION);
    bool show_fps = false;
    if (show_fps)
    {
        char fps[32];
        snprintf(fps, sizeof(fps), "FPS: %.1f", state.fps);
        state.footbar_right_text = state.footbar_right_text + " | " + fps;
    }
    const char* text = state.footbar_right_text.c_str();
    float text_w = ImGui::CalcTextSize(text).x;
    ImGui::SetCursorPos(ImVec2(w - text_w - pad, y));
    ImGui::Text("%s", text);

    ImGui::EndChild();
    ImGui::PopStyleColor();
}

/*****************************************************************************/

/* Private Methods - Draw Exit Pop-Up */

void MainUI::draw_exit_popup()
{
    ImGuiIO& io = *(context.io);

    if (state.exit_request)
    {
        state.exit_request = false;
        ImGui::OpenPopup("exit_popup");
    }

    // Center pop-up
    ImGui::SetNextWindowPos(
        ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f),
        ImGuiCond_Always,
        ImVec2(0.5f, 0.5f)
    );

    static constexpr float popup_width = 420.0f;
    static constexpr float popup_height = 130.0f;
    ImGui::SetNextWindowSize(
        ImVec2(popup_width, popup_height),
        ImGuiCond_Always
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings;

    if (ImGui::BeginPopupModal("exit_popup", nullptr, flags))
    {
        // Text: Exit the App?
        ImGui::Dummy(ImVec2(0, 10));
        ImGui::PushFont(state.font_h2);
        const char* title = "Quit App?";
        float text_width = ImGui::CalcTextSize(title).x;
        ImGui::SetCursorPosX(
            (ImGui::GetContentRegionAvail().x - text_width) * 0.5f
        );
        ImGui::TextUnformatted(title);
        ImGui::PopFont();

        // Button: Exit
        const ImVec2 button_size(120.0f, 30.0f);
        float spacing = 20.0f;
        float total = button_size.x * 2 + spacing;
        ImGui::Dummy(ImVec2(0, 20));
        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - total) * 0.5f);
        if (ImGui::Button("Exit", button_size))
        {
            state.running = false;
            ImGui::CloseCurrentPopup();
        }

        // Button: Cancel
        ImGui::SameLine(0, spacing);
        if (ImGui::Button("Cancel", button_size))
        {   ImGui::CloseCurrentPopup();   }

        ImGui::EndPopup();
    }
}

void MainUI::change_theme()
{
    using e_theme = AppState::e_theme;

    uint32_t theme = static_cast<uint32_t>(state.theme);
    theme = (theme + 1U) % state.NUM_THEMES;
    state.theme = static_cast<e_theme>(theme);

    switch(state.theme)
    {
        case e_theme::DARK:
            ImGui::StyleColorsDark();
            break;
        case e_theme::LIGHT:
            ImGui::StyleColorsLight();
            break;
        case e_theme::CLASSIC:
            ImGui::StyleColorsClassic();
            break;
        default:
            break;
    }
}

/*****************************************************************************/
