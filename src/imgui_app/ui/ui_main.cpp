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
#include <cstring>

// Imgui Libraries
#include "imgui.h"

/*****************************************************************************/

/* Fonts Configuration */

// Note: font names at custom_fonts.h (_fonts array)
static constexpr const char* FONT_INIT = "NK57_Monospace_No_Bk_otf";

static constexpr float FONT_H1_SIZE = 32.0f;
static constexpr float FONT_H2_SIZE = 24.0f;
static constexpr float FONT_H3_SIZE = 18.0f;
static constexpr float FONT_TEXT_SIZE = 14.0f;

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
    AppState::Font font_load;

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
    font_load.name = "Default";
    font_load.type = AppState::e_font_type::TEXT;
    font_load.imgui = context.io->Fonts->AddFontDefault();
    context.io->FontDefault = font_load.imgui;

    // Load Custom Fonts
    for (std::size_t i = 0U; i < binary_fonts.count(); ++i)
    {
        s_font_data* font = binary_fonts.get(i);
        if (font)
        {
            font_load.bin = font;
            font_load.name = font->name;

            font_load.type = AppState::e_font_type::H1;
            font_load.imgui = add_font(font->data, font->size, FONT_H1_SIZE);
            state.fonts.emplace_back(font_load);

            font_load.type = AppState::e_font_type::H2;
            font_load.imgui = add_font(font->data, font->size, FONT_H2_SIZE);
            state.fonts.emplace_back(font_load);

            font_load.type = AppState::e_font_type::H3;
            font_load.imgui = add_font(font->data, font->size, FONT_H3_SIZE);
            state.fonts.emplace_back(font_load);

            font_load.type = AppState::e_font_type::TEXT;
            font_load.imgui = add_font(font->data, font->size, FONT_TEXT_SIZE);
            state.fonts.emplace_back(font_load);
        }
        else
        {   std::printf("Warning: Fail to load font \"%s\"\n", font->name);   }
    }

    // Create list of fonts names
    state.font_names.reserve(state.fonts.size());
    for (const auto& font : state.fonts)
    {
        bool name_already_added = false;
        for (const char* name : state.font_names)
        {
            if (std::strcmp(name, font.name) == 0)
            {
                name_already_added = true;
                break;
            }
        }

        if (!name_already_added)
        {   state.font_names.push_back(font.name);   }
    }

    // Set initial font to use
    for (size_t i = 0; i < state.font_names.size(); ++i)
    {
        if (std::string(state.font_names[i]) == std::string(FONT_INIT))
        {
            state.selected_font = i;
            break;
        }
    }

    // When viewports are enabled we tweak WindowRounding/WindowBg so
    // platform windows can look identical to regular ones
    if (context.io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        context.style->WindowRounding = 0.0f;
        context.style->Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
}

bool MainUI::set_font(const char* name, const AppState::e_font_type type)
{
    bool font_found = false;

    for (const auto& font : state.fonts)
    {
        if (strcmp(font.name, name) != 0)
        {   continue;   }

        if (font.type != type)
        {   continue;   }

        font_found = true;

        ImGui::PushFont(font.imgui);
        return true;
    }

    if (!font_found)
    {   std::printf("Warning: Fail to set font \"%s\"\n", name);   }

    return false;
}

void MainUI::draw()
{
    /* Main UI Window */

    using e_font_type = AppState::e_font_type;

    // Get current FPS
    state.fps = ImGui::GetIO().Framerate;

    // Get current used Imgui style
    context.style = &(ImGui::GetStyle());

    const bool text_font_pushed = set_font(
        state.font_names[state.selected_font], e_font_type::TEXT);
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
    if (text_font_pushed)
    {   ImGui::PopFont();   }
}

/*****************************************************************************/

/* Private Methods - Setup */

ImFont* MainUI::add_font(const uint8_t* data, const size_t data_len,
    const float size)
{
    void* ptr_data = const_cast<void*>(static_cast<const void*>(data));
    int _data_len = static_cast<int>(data_len);

    ImFontConfig config;
    config.FontDataOwnedByAtlas = false;

    auto& Fonts = context.io->Fonts;
    return Fonts->AddFontFromMemoryTTF(ptr_data, _data_len, size, &config);
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
    const bool heading_font_pushed = set_font(
        state.font_names[state.selected_font], AppState::e_font_type::H2);
    ImGui::Text("ImGui C++ Starter");
    if (heading_font_pushed)
    {   ImGui::PopFont();   }

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

    // Combobox: Font Selector
    int new_selection = state.selected_font;
    int i = 0;
    ImGui::Combo("Selected Font", &new_selection, state.font_names.data(),
        static_cast<int>(state.font_names.size()));
    if (new_selection != state.selected_font)
    {   state.selected_font = new_selection;   }

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
    using e_font_type = AppState::e_font_type;
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
        const bool heading_font_pushed = set_font(
            state.font_names[state.selected_font], e_font_type::H2);
        const char* title = "Quit App?";
        float text_width = ImGui::CalcTextSize(title).x;
        ImGui::SetCursorPosX(
            (ImGui::GetContentRegionAvail().x - text_width) * 0.5f
        );
        ImGui::TextUnformatted(title);
        if (heading_font_pushed)
        {   ImGui::PopFont();   }

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
