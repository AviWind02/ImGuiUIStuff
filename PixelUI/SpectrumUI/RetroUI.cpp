#include "../common.h"
#include <functional>

namespace RetroBaseUI {
    // Global Variables
    std::string subTitle = "MainMenu";
    std::string textDescription = "description Box";

    ImVec2 menuPos = { 1, 15 };
    ImVec2 menuSize = { 475.f, 775.f };

    float openstate = 475.f;
    float closedstate = 50.f;
    float pushstate = 25.f;

    POINT lastMousePos = { 0, 0 };
    bool hasMenuOpenFinished;

    // Font
    extern ImFont* m_font_big;

    int buttonCounter;
    int subMenuOptionCount;
    int subMenucurrentOptionCount;
    int fadeStage;
    int frametimeRGB;


    float fadeProgress;
    const float ButtonSizeXChild = 180.f;
    const float ButtonSizeX = 190.f;
    const float ButtonSizeY = 30.f;
    const float CursorPosX = 70.f;

    // Colors
    ImVec4 White = ImColor(255, 255, 255, 255);
    ImVec4 spectrumpurple = ImColor(245, 176, 236);
    ImVec4 spectrumpink = ImColor(237, 155, 188);
    ImVec4 spectrumcreamdark = ImColor(242, 185, 176);
    ImVec4 spectrumcreamlist = ImColor(250, 222, 158);
    ImVec4 spectrumcreamdarkLowalpha = ImColor(242, 185, 176, 100);
    ImVec4 LowGrey = ImColor(25, 25, 25, 125);
    ImVec4 LowGrey150 = ImColor(25, 25, 25, 150);
    ImVec4 darkGrey = ImColor(0, 0, 0, 225);
    ImVec4 Black = ImColor(0, 0, 0, 255);

    // Window Sizes
    ImVec2 defaultDescriptionWindowSize = ImVec2(481, 153);
    ImVec2 defaultDescriptionWindowPos = ImVec2(1433, 856);

    // Menu State
    bool isMenuOpen = true;

    void dx_init() {
        auto& style = ImGui::GetStyle();
        style.WindowPadding = { 10.f, 10.f };
        style.FramePadding = { 8.f, 4.f };
        style.ItemSpacing = { 10.f, 6.f };
        style.ItemInnerSpacing = { 6.f, 6.f };
        style.TouchExtraPadding = { 0.f, 0.f };
        style.IndentSpacing = 21.f;
        style.ScrollbarSize = 10.f;
        style.GrabMinSize = 8.f;
        style.PopupBorderSize = 1.f;
        style.FrameBorderSize = 1.f;
        style.TabBorderSize = 0.f;
        style.ChildRounding = 3.f;
        style.FrameRounding = 3.f;
        style.WindowRounding = 11.f;
        style.ScrollbarRounding = 0.f;
        style.GrabRounding = 0.f;
        style.TabRounding = 0.f;
        style.WindowTitleAlign = { 0.5f, 0.5f };
        style.ButtonTextAlign = { 0.f, 0.f };
        style.DisplaySafeAreaPadding = { 3.f, 3.f };

        auto& colors = style.Colors;
        colors[ImGuiCol_Text] = White;
        colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 0.90f, 0.19f, 1.00f);
        colors[ImGuiCol_WindowBg] = darkGrey;
        colors[ImGuiCol_ChildBg] = LowGrey150;
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = spectrumcreamlist;
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = spectrumcreamdarkLowalpha;
        colors[ImGuiCol_FrameBgHovered] = LowGrey;
        colors[ImGuiCol_FrameBgActive] = LowGrey;
        colors[ImGuiCol_TitleBg] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_CheckMark] = spectrumpink;
        colors[ImGuiCol_SliderGrab] = spectrumpink;
        colors[ImGuiCol_SliderGrabActive] = spectrumpurple;
        colors[ImGuiCol_Button] = Black;
        colors[ImGuiCol_ButtonHovered] = LowGrey;
        colors[ImGuiCol_ButtonActive] = spectrumpink;
        colors[ImGuiCol_Header] = ImVec4(0.37f, 0.37f, 0.37f, 0.31f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.38f, 0.38f, 0.37f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.37f, 0.37f, 0.37f, 0.51f);
        colors[ImGuiCol_Separator] = spectrumpink;
        colors[ImGuiCol_SeparatorHovered] = spectrumpink;
        colors[ImGuiCol_SeparatorActive] = spectrumpink;
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        colors[ImGuiCol_Tab] = ImVec4(0.21f, 0.21f, 0.21f, 0.86f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.27f, 0.27f, 0.27f, 0.86f);
        colors[ImGuiCol_TabActive] = ImVec4(0.34f, 0.34f, 0.34f, 0.86f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.10f, 0.10f, 0.97f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }

    void UpdateFadeProgress() {
        if ((timeGetTime() - frametimeRGB) > 15) {
            fadeProgress += 0.01f;

            if (fadeProgress >= 1.0f) {
                fadeProgress = 0.0f;
                fadeStage = (fadeStage + 1) % 5;
            }

            frametimeRGB = timeGetTime();
        }
    }

    ImVec4 GetCurrentFadeColor() {
        UpdateFadeProgress();
        ImVec4 startColor, endColor;

        switch (fadeStage) {
        case 0:
            startColor = spectrumpurple;
            endColor = spectrumpink;
            break;
        case 1:
            startColor = spectrumpink;
            endColor = spectrumcreamdark;
            break;
        case 2:
            startColor = spectrumcreamdark;
            endColor = spectrumcreamlist;
            break;
        case 3:
            startColor = spectrumcreamlist;
            endColor = spectrumcreamdarkLowalpha;
            break;
        case 4:
            startColor = spectrumcreamdarkLowalpha;
            endColor = spectrumpurple;
            break;
        default:
            startColor = spectrumpurple;
            endColor = spectrumpink;
            break;
        }

        return ImVec4(
            startColor.x + (endColor.x - startColor.x) * fadeProgress,
            startColor.y + (endColor.y - startColor.y) * fadeProgress,
            startColor.z + (endColor.z - startColor.z) * fadeProgress,
            startColor.w + (endColor.w - startColor.w) * fadeProgress
        );
    }

    void EnlargeMenu() {
        static int frametime = 0;

        if ((timeGetTime() - frametime) > 25) {
            if (isMenuOpen) {
                if (menuSize.x < openstate)
                    menuSize.x += pushstate;
                else
                    hasMenuOpenFinished = true;
            }
            else {
                if (menuSize.x > closedstate)
                    menuSize.x -= pushstate;
                hasMenuOpenFinished = false;
            }
            frametime = timeGetTime();
        }
    }

    bool IsButtonInChildWindow() {
        ImGuiWindow* currentWindow = ImGui::GetCurrentWindow();
        return currentWindow->Flags & ImGuiWindowFlags_ChildWindow;
    }

    void DrawVerticalLineFromTop(ImVec4 color, float xPos, float thickness, float menuHeight) {
        ImVec2 startPos = ImVec2(xPos, menuPos.y);
        ImVec2 endPos = ImVec2(xPos, menuPos.y + menuHeight);
        ImGui::GetCurrentWindow()->DrawList->AddLine(startPos, endPos, ImGui::GetColorU32(color), thickness);
    } 

    void DescriptionBox(const std::string& text, bool showOnMouse)
    {
        static ImVec2 descriptionWindowPos = defaultDescriptionWindowPos;
        static ImVec4 descriptionBackgroundColor = Black;
        static ImVec4 descriptionTextColor = White;
        const float xPosOffset = 15.f;
        const float yPosOffset = 5.f;
        const float ySizeOffset = 15.f;


 
        float wrapWidth = ImGui::GetWindowSize().x;
        // Calculate the size of the window based on the text length with wrapping
        ImVec2 textSize = ImGui::CalcTextSize(text.c_str(), nullptr, false, wrapWidth);
        ImVec2 descriptionWindowSize = ImVec2(wrapWidth + 20.0f, textSize.y + 20.0f); //Add some padding

        // Get the current cursor position
        ImVec2 cursorPos = ImGui::GetMousePos();
        ImVec2 Pos = { cursorPos.x + xPosOffset, cursorPos.y + yPosOffset };

        if (!showOnMouse)
        {
            Pos = { menuPos.x, (menuPos.y + menuSize.y) + yPosOffset };
            descriptionWindowSize = { menuSize.x, (textSize.y + ySizeOffset) };
        }
        
    
        ImGui::SetNextWindowPos(Pos);
        ImGui::SetNextWindowSize(descriptionWindowSize);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, descriptionBackgroundColor);

        // Create the window
        if (ImGui::Begin("Description", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar))
        {
            ImGui::PushTextWrapPos(textSize.x);
            ImGui::TextWrapped("%s", text.c_str());
            ImGui::PopTextWrapPos();
        }

        ImGui::PopStyleColor();
        ImGui::End();
    }


    void OnHoverShowDescription(const std::string& text)
    {
        if (ImGui::IsItemHovered())
        {
            DescriptionBox(text, false);
        }
    }

    bool Sub(std::string text) {
        subMenuOptionCount++;
        bool selecting = (subMenucurrentOptionCount == subMenuOptionCount);

        // Offsets and positions
        const float iconWidth = 45.f;
        const float iconHeight = 65.f;
        const float textOffsetX = -2.5f;
        const float textOffsetYBase = 60.f;
        const float textOffsetYAdjustment = -45.f;
        float yPos = (textOffsetYBase * subMenuOptionCount) + textOffsetYAdjustment;

        ImVec2 textPos{ menuPos.x + textOffsetX, menuPos.y + yPos };

        bool hoverMouse, held;
        bool pressed = control::MouseClick(text.c_str(), textPos, ImVec2(iconWidth, iconHeight), &hoverMouse, &held);

        // Draw the icon using the raw data from a TFF file by fr0hawk
        draw::Text(text, hoverMouse ? spectrumpink : spectrumcreamlist, textPos, m_font_icon);

        return (hoverMouse && pressed);
    }

    bool Option(std::string option) {
        float buttonSizeX_ = ButtonSizeX;
        if (buttonCounter % 2 == 1) {
            ImGui::SameLine();
        }
        else if (!IsButtonInChildWindow()) {
            ImGui::SetCursorPosX(CursorPosX);
        }
        ImGui::PushStyleColor(ImGuiCol_Border, spectrumcreamlist);
        bool result = ImGui::Button(option.c_str(), { IsButtonInChildWindow() ? ButtonSizeXChild : buttonSizeX_, ButtonSizeY });
        ImGui::PopStyleColor();
        OnHoverShowDescription("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque euismod, felis vel facilisis vehicula, ligula ex fringilla quam, nec laoreet est ligula nec justo. Nam hendrerit, justo non dapibus fermentum, turpis urna bibendum metus, sed interdum elit velit et mauris. Vestibulum vehicula imperdiet mi, ");
        buttonCounter++;
        return result;
    }

    bool Toggle(std::string option, bool* toggle) {
        const ImVec2 pad = ImVec2(2.0f, 5.0f);
        const float square_sz = 30.0f;
        if (buttonCounter % 2 == 1) {
            ImGui::SameLine();
        }
        else if (!IsButtonInChildWindow()) {
            ImGui::SetCursorPosX(CursorPosX);
        }
        ImGui::PushStyleColor(ImGuiCol_Border, spectrumcreamlist);
        bool result = ImGui::Button(option.c_str(), { IsButtonInChildWindow() ? ButtonSizeXChild : ButtonSizeX, ButtonSizeY });
        ImGui::PopStyleColor();

        if (result) {
            *toggle = !(*toggle);
        }

        ImVec2 button_pos = ImGui::GetItemRectMin();
        float checkbox_x_pos = button_pos.x + (IsButtonInChildWindow() ? 150.f : 160.f);
        float checkbox_y_pos = button_pos.y + (30.0f - square_sz) / 2;

        ImVec2 check_bb_min = ImVec2(checkbox_x_pos, checkbox_y_pos);
        ImVec2 check_bb_max = ImVec2(checkbox_x_pos + square_sz, checkbox_y_pos + square_sz);
        ImGui::RenderFrame(check_bb_min, check_bb_max, ImGui::GetColorU32(ImGuiCol_Button), true, ImGui::GetStyle().FrameRounding);

        if (*toggle) {
            ImVec2 check_bb_center = ImVec2(((check_bb_min.x + check_bb_max.x) * 0.5f) - 13.f, ((check_bb_min.y + check_bb_max.y) * 0.5f) - 12.f);
            ImGui::RenderCheckMark(check_bb_center, ImGui::GetColorU32(ImGuiCol_CheckMark), square_sz - pad.x * 2.0f);
        }

        buttonCounter++;
        return result;
    }

    bool DropDown(std::string option, float sizeH, std::function<void()> renderContent) {
        static bool dropdownOpen = false;
        buttonCounter = 0;

        ImGui::SetCursorPosX(CursorPosX);

        std::string T = "###" + option;
        ImGui::PushStyleColor(ImGuiCol_Border, spectrumcreamlist);
        bool buttonClicked = ImGui::Button(option.c_str(), ImVec2(menuSize.x - 85, ButtonSizeY));
        ImGui::PopStyleColor();

        ImGuiWindow* window = ImGui::GetCurrentWindow();
        ImRect bb = window->DC.LastItemRect;
        ImVec2 size = bb.GetSize();
        ImU32 text_col = ImGui::GetColorU32(ImGuiCol_Text);

        if (buttonClicked) {
            dropdownOpen = !dropdownOpen;
        }

        ImVec2 arrow_pos = ImVec2(bb.Min.x + size.x - 20.0f, bb.Min.y + (size.y - ImGui::GetFontSize()) * 0.5f);
        ImGui::RenderArrow(window->DrawList, arrow_pos, text_col, dropdownOpen ? ImGuiDir_Up : ImGuiDir_Down);

        if (dropdownOpen) {
            ImGui::SetNextWindowPos(ImVec2(bb.Min.x, bb.Min.y + ButtonSizeY));
            ImGui::SetNextWindowSize(ImVec2(menuSize.x - 85, sizeH));
            if (ImGui::BeginChild(T.c_str(), ImVec2(menuSize.x - 85, 300.0f), true)) {
                renderContent();
                ImGui::EndChild();
            }
        }

        return buttonClicked;
    }

    bool DragIntWithButton(const char* label, int* v, int v_min, int v_max, int step) {
        buttonCounter = 0;
        ImVec2 textSize = ImGui::CalcTextSize(label);
        if (!IsButtonInChildWindow())
            ImGui::SetCursorPosX(CursorPosX);

        ImGui::Text(label);
        ImGui::SameLine();
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 8.f });
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
        ImGui::PushStyleColor(ImGuiCol_Button, spectrumpink);

        bool keyleft = ImGui::ArrowButton(((std::string)label + "ID:Left").c_str(), ImGuiDir_Left);
        ImGui::SameLine();
        ImGui::PushItemWidth((menuSize.x - (IsButtonInChildWindow() ? 165.f : 150.f)) - (textSize.x));
        bool keydrag = ImGui::DragInt(("###" + (std::string)label).c_str(), v, .05f, v_min, v_max);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        bool keyright = ImGui::ArrowButton(((std::string)label + "ID:Right").c_str(), ImGuiDir_Right);
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);

        if (keyright) {
            if (*v < v_max)
                *v += step;
            else
                *v = v_min;
        }
        else if (keyleft) {
            if (*v > v_min)
                *v -= step;
            else
                *v = v_max;
        }
        return keyleft || keydrag || keyright;
    }

    bool DragFloatWithButton(const char* label, float* v, float v_min, float v_max, float step, const char* format = "%.3f") {
        buttonCounter = 0;
        ImVec2 textSize = ImGui::CalcTextSize(label);
        if (!IsButtonInChildWindow())
            ImGui::SetCursorPosX(CursorPosX);

        ImGui::Text(label);
        ImGui::SameLine();
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 8.f });
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
        ImGui::PushStyleColor(ImGuiCol_Button, spectrumpink);

        bool keyleft = ImGui::ArrowButton(((std::string)label + "ID:Left").c_str(), ImGuiDir_Left);
        ImGui::SameLine();
        ImGui::PushItemWidth((menuSize.x - (IsButtonInChildWindow() ? 165.f : 150.f)) - (textSize.x));
        bool keydrag = ImGui::DragFloat(("###" + (std::string)label).c_str(), v, .05f, v_min, v_max, format);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        bool keyright = ImGui::ArrowButton(((std::string)label + "ID:Right").c_str(), ImGuiDir_Right);
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);

        if (keyright) {
            if (*v < v_max)
                *v += step;
            else
                *v = v_min;
        }
        else if (keyleft) {
            if (*v > v_min)
                *v -= step;
            else
                *v = v_max;
        }
        return keyleft || keydrag || keyright;
    }

    void CreateImGuiWindow(const char* title, const char* body) {
        ImVec2 displaySize = ImGui::GetIO().DisplaySize;
        ImVec2 windowSize(600, 450);
        ImVec2 windowPos = ImVec2((displaySize.x - windowSize.x) / 2, (displaySize.y - windowSize.y) / 2);

        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowPos(windowPos);
        if (ImGui::Begin(title, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse)) {
            ImGui::TextWrapped("%s", body);

            ImGui::Spacing();
            ImGui::Dummy(ImVec2(0.0f, ImGui::GetContentRegionAvail().y - ImGui::GetTextLineHeightWithSpacing() * 2));

            ImGui::SetCursorPosX(windowSize.x - 110);
            if (ImGui::Button("Okay")) {
                // Action for Okay button
            }
        }
        ImGui::End();
    }

    std::string formattedTestString =
        "Welcome to Spectrum Cheats\n"
        "Base: built by bomuld\n"
        "This is a closed Menu not for sales. This menu can be shared, be sure to add the origin creator Avi. This menu is just a simple cheat for GTA 5 to have fun with.\n\n"
        "Controls for this menu:\n"
        "This menu is fully ImGui with mouse support. It does not have controller support for the buttons.\n\n"
        "Clicking on this will allow you to change the bind (soon).\n"
        "Insert key to switch menus\n"
        "X key is used to display the mouse\n"
        "F4 to open the menu.\n\n"
        "Once again, thank you for using Spectrum. Have fun!";

    int test1;
    bool test2;
#define ICON_self "a"
#define ICON_settings "b"
#define ICON_Misc "c"
#define ICON_Creatertool "d"
#define ICON_Recovery "e"
#define ICON_Onlineplayers "f"
#define ICON_OnlineJoiner "g"
#define ICON_Online "h"
#define ICON_Teleports "i"
#define ICON_Weaponloadout "j"
#define ICON_weapons "k"
#define ICON_vehicle "l"
#define ICON_spawnvehicle "l2"
#define ICON_Clothing "m"
    void Menu() {
        buttonCounter = 0;
        subMenuOptionCount = 0;
        control::ControlTick();
        EnlargeMenu();

        ImGui::SetNextWindowPos(menuPos);
        ImGui::SetNextWindowSize(menuSize);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(ImColor(0, 0, 0, 175)));
        ImGui::PushStyleColor(ImGuiCol_Border, spectrumcreamlist);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 2.f);

        if (ImGui::Begin("Background", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus)) {
            if (isMenuOpen)
                DrawVerticalLineFromTop(spectrumcreamlist, 50, 2.f, menuSize.y);

            CreateImGuiWindow("Spectrum Cheats V1", formattedTestString.c_str());

            Sub(ICON_self);
            Sub(ICON_Clothing);
            Sub(ICON_spawnvehicle);
            Sub(ICON_weapons);
            Sub(ICON_Teleports);
            Sub(ICON_Weaponloadout);
            Sub(ICON_Online);
            Sub(ICON_Onlineplayers);
            Sub(ICON_OnlineJoiner);
            Sub(ICON_Creatertool);
            Sub(ICON_Recovery);
            Sub(ICON_Misc);


            bool showDropdown = DropDown("Select an option", 400, [&]() {
                DragIntWithButton("Ear Accessories Style", &test1, 1, 100, 1);
                DragIntWithButton("Head Gear", &test1, 1, 100, 1);
                Option("Increase Health");
                Toggle("Toggle Stamin", &test2);
                Toggle("Toggle Stamin2", &test2);
            });
            Toggle("Toggle God Mode", &test2);
            Toggle("Toggle Stamin", &test2);
            Option("Clear Wanted Level1");
            Option("Clear Wanted Level2");
            Option("Clear Wanted Level3");
            Option("Increase Health");
            Option("Increase Stamina");
            Option("Enable God Mode");
            DragIntWithButton("Ear Accessories Style", &test1, 1, 100, 1);
            DragIntWithButton("Head Gear", &test1, 1, 100, 1);
            Option("Increase Health");
            Option("Increase Stamina");
            Option("Enable God Mode");
            DragIntWithButton("Ear Accessories Style", &test1, 1, 100, 1);
            DragIntWithButton("Head Gear", &test1, 1, 100,1     );
        }

        ImGui::PopStyleVar();
        ImGui::PopStyleColor(2);
        ImGui::End();
    }
} // namespace RetroBaseUI
