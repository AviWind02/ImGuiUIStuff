#include "../common.h"
#include <functional>
#include <algorithm>

namespace SideUI {

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

    std::string subTitle = "Vehicle Spawner";
    std::string textDescription = "description Box";
    ImVec2 menuPos = { -11, -14 };
    ImVec2 menuSize = { 450.f, 775.f };
    ImVec2 mainMenuSize = { 50, 775.f };
    int maxOption = 27;
    float scrollerY = 0.0f;
    float scrollerSpeed = 0.1f;
    float startY = 0.0f;
    POINT lastMousePos = { 0, 0 };

    ImVec4 defaultTextColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 defaultBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
    ImVec4 middleBoxBackColor = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    ImVec4 scrollBarColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    ImVec4 scrollBarColorClicked = ImVec4(1.f, 0.5f, 0.5f, 1.0f);
    ImVec4 textOnHoverColor = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 textOnSelecltedColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 textOnNormalColor = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
    ImVec4 bottomEndBoxColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    ImVec4 bottomEndBoxColor2 = ImVec4(1.f, 1.f, 0.2f, 1.0f);

    ImVec2 optionSize = ImVec2(400, 25);
    ImVec2 optionSizeBox = ImVec2(menuSize.x, 750);
    ImVec2 footerSize = ImVec2(optionSize.x, optionSize.y);
    ImVec2 headerSize = ImVec2(optionSize.x, 80);
    ImVec2 descriptionTextOffset = ImVec2(10.0f, 2.0f);

    float optionYOffset = 25.f;
    float optionXOffset = 50.f;
    float optionYStart = 0.0f;
    float headerOffsetX = 4.f;
    float rightSideTextOffet = 58.f;

    int subMenuOptionCount = 0;
    int subMenucurrentOptionCount = 0;

    ImVec2 maxSize = { 50, optionSizeBox.y };
    ImVec2 minSize = { 50, 50.f };
    static ImVec2 currentSize = minSize;

    bool isMenuOpen = false;
    bool useSmallerWindow = false;
    bool moveToTop = false;


    bool containsIcon(const std::string& text) {
        for (size_t i = 0; i < text.size(); i++) {
            unsigned char c = text[i];
            if (c >= 0xe0 && c <= 0xf8) { // Check if the first byte is in the Font Awesome range
                if (i + 2 < text.size() && (unsigned char)text[i + 1] >= 0x80 && (unsigned char)text[i + 2] >= 0x80) {
                    return true; // Found an icon character
                }
            }
        }
        return false; // No icon found
    }

    std::string GetOptionIDInString()
    {
        return std::to_string(optionCount);
    }

    bool DrawTextOnOption(const std::string& Ltext, const std::string Ctext, const std::string& Rtext) {

        optionCount++;

        int startOption = (currentOption - 1) / maxOption * maxOption + 1;
        int endOption = startOption + maxOption - 1;
        static int iconOffset;

        if (optionCount >= startOption && optionCount <= endOption) {
            float yPosition = (optionYOffset * (optionCount - startOption + 1) + optionYStart) + menuPos.y;
            ImVec2 textPos = ImVec2(menuPos.x + optionXOffset, yPosition);

            static float smoothScrollYPosition = yPosition;
            float scrollSpeed = 0.1f;
            ImVec2 smoothTextPos = ImVec2(menuPos.x + optionXOffset, smoothScrollYPosition);

            float fadeAlpha = std::clamp((currentSize.y - minSize.y) / (maxSize.y - minSize.y), 0.0f, 1.0f);
            ImVec4 textColor = ImVec4(textOnNormalColor.x, textOnNormalColor.y, textOnNormalColor.z, fadeAlpha);

            ImVec2 mousePos = ImGui::GetMousePos();
            ImVec2 optionEndPos = ImVec2(textPos.x + optionSize.x, textPos.y + optionSize.y);

            bool clicked = (mousePos.x >= textPos.x && mousePos.x <= optionEndPos.x &&
                mousePos.y >= textPos.y && mousePos.y <= optionEndPos.y) &&
                ImGui::IsMouseClicked(ImGuiMouseButton_Left);

            bool hovered = (mousePos.x >= textPos.x && mousePos.x <= optionEndPos.x &&
                mousePos.y >= textPos.y && mousePos.y <= optionEndPos.y);

            if (clicked) {
                currentOption = optionCount;
            }

            bool selectedOption = (currentOption == optionCount);

            if (isMenuOpen) {
                if (selectedOption) {
                    smoothScrollYPosition += (yPosition - smoothScrollYPosition) * scrollSpeed;
                }

                if (hovered) {
                    draw::RectFilled(scrollBarColor, textPos, optionSize, ImDrawCornerFlags_Left, 7.5f);
                }

                if (selectedOption) {
                    draw::RectFilled(scrollBarColorClicked, smoothTextPos, optionSize, ImDrawCornerFlags_Left, 7.5f);
                }

                draw::Text(Ltext, hovered ? textOnHoverColor : textColor,
                    { textPos.x + descriptionTextOffset.x, textPos.y + descriptionTextOffset.y });

                if (containsIcon(Rtext) || containsIcon(Ctext))
                    iconOffset = 3.f;

                if (Rtext != "NULL") {
                    draw::Text(Rtext, hovered ? textOnHoverColor : textColor,
                        { textPos.x + descriptionTextOffset.x - rightSideTextOffet, (textPos.y + descriptionTextOffset.y) + iconOffset },
                        nullptr, true);
                }

                if (Ctext != "NULL") {
                    draw::Text(Ctext, hovered ? textOnHoverColor : textColor,
                        { textPos.x + descriptionTextOffset.x - rightSideTextOffet, (textPos.y + descriptionTextOffset.y) + iconOffset },
                        nullptr, false, true);
                }
            }

            if (selectedOption && (clicked || control::selectPressed)) {
                control::selectPressed = false;
                return true;
            }
        }

        return false;
    }



    bool DrawIntOption(const std::string& optionName, int& value, int min, int max, int step, bool useToggle, bool& toggle) {

        if (!isMenuOpen)
            return false;

        bool optionClicked = false;
        bool toggleChanged = false;
        bool valueChanged = false;

        if (useToggle)
            optionClicked = DrawTextOnOption(optionName, "NULL", toggle ? ICON_FA_TOGGLE_ON : ICON_FA_TOGGLE_OFF);
        else
            optionClicked = DrawTextOnOption(optionName, "NULL", "NULL");      

        bool selectedOption = (currentOption == optionCount);


        int startOption = (currentOption - 1) / maxOption * maxOption + 1;
        int endOption = startOption + maxOption - 1;

        if (optionCount >= startOption && optionCount <= endOption)
        {

            float yPosition = (optionYOffset * (optionCount - startOption + 1) + optionYStart) + menuPos.y;
            ImVec2 textPos = ImVec2(menuPos.x, yPosition);
            ImVec2 sliderPos = ImVec2(textPos.x + optionSize.x - 125.f, textPos.y + 17.f);

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, .5f));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 1));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 1.f);
            ImGui::PushStyleColor(ImGuiCol_FrameBg, defaultBackgroundColor);
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, textOnNormalColor);
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.5f, 0.0f, 0.0f));


            ImGui::SetCursorScreenPos(sliderPos);
            ImGui::PushItemWidth(useToggle ? 152.5f : 181.f);
            valueChanged = ImGui::SliderInt((("##" + GetOptionIDInString()) + optionName).c_str(), &value, min, max);

    /*        if (useToggle)
            {
                ImGui::SameLine(0.f);
                toggleChanged = ImGui::Checkbox((("##Toggle_" + GetOptionIDInString()) + optionName).c_str(), &toggle);
            }*/

            if (valueChanged || toggleChanged)
                currentOption = optionCount;
            ImGui::PopItemWidth();

            if (optionClicked)
            {
                toggle = !toggle;
            }

            if (selectedOption) {
                if (control::leftPressed) {
                    value -= step;
                    if (value < min) value = max;
                    valueChanged = true;
                }
                if (control::rightPressed) {
                    value += step;
                    if (value > max) value = min;
                    valueChanged = true;
                }
            }

            ImGui::PopStyleColor(3);
            ImGui::PopStyleVar(3);
        }

        return optionClicked || valueChanged;
    }
    bool DrawFloatOption(const std::string& optionName, float& value, float min, float max, float step, bool useToggle, bool& toggle) {


        if (!isMenuOpen)
            return false;

        bool optionClicked = false;
        bool toggleChanged = false;
        bool valueChanged = false;

        if (useToggle)
            optionClicked = DrawTextOnOption(optionName, "NULL", toggle ? ICON_FA_TOGGLE_ON : ICON_FA_TOGGLE_OFF);
        else
            optionClicked = DrawTextOnOption(optionName, "NULL", "NULL");


        bool selectedOption = (currentOption == optionCount);


        int startOption = (currentOption - 1) / maxOption * maxOption + 1;
        int endOption = startOption + maxOption - 1;

        if (optionCount >= startOption && optionCount <= endOption)
        {


            float yPosition = (optionYOffset * (optionCount - startOption + 1) + optionYStart) + menuPos.y;
            ImVec2 textPos = ImVec2(menuPos.x, yPosition);
            ImVec2 sliderPos = ImVec2(textPos.x + optionSize.x - 125.f, textPos.y + 17.f);

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, .5f));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 2));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 1.f);
            ImGui::PushStyleColor(ImGuiCol_FrameBg, defaultBackgroundColor);
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, textOnNormalColor);
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.5f, 0.0f, 0.0f));


            ImGui::SetCursorScreenPos(sliderPos);
            ImGui::PushItemWidth(useToggle ? 152.5f : 181.f);
            valueChanged = ImGui::SliderFloat((("##" + GetOptionIDInString()) + optionName).c_str(), &value, min, max);

         /*   if (useToggle)
            {
                ImGui::SameLine(0.f);
                toggleChanged = ImGui::Checkbox((("##Toggle_" + GetOptionIDInString()) + optionName).c_str(), &toggle);
            }*/

            if (valueChanged || toggleChanged)
                currentOption = optionCount;
            ImGui::PopItemWidth();


            if (optionClicked)
            {
                toggle = !toggle;
            }

            if (selectedOption) {
                if (control::leftPressed) {
                    value -= step;
                    if (value < min) value = max;
                    valueChanged = true;
                }
                if (control::rightPressed) {
                    value += step;
                    if (value > max) value = min;
                    valueChanged = true;
                }
            }

            ImGui::PopStyleColor(3);
            ImGui::PopStyleVar(3);
        }

        return optionClicked || valueChanged;
    }


    void DrawMainMenu() {
        float speed = 15.0f;
        static float horizontalCurrentWidth = 0.0f;
        static bool useAllCorners = true;

        if (isMenuOpen) {

            useSmallerWindow = false;

            if (currentSize.y < maxSize.y) {
                currentSize.y += speed;
                if (currentSize.y > maxSize.y) {
                    currentSize.y = maxSize.y;
                }
                useAllCorners = false;
            }
        }
        else {
            if (horizontalCurrentWidth > 0.0f) {
                horizontalCurrentWidth -= speed;
                if (horizontalCurrentWidth <= 0.0f) {
                    horizontalCurrentWidth = 0.0f;
                }
            }
            else if (currentSize.y > minSize.y) {
                currentSize.y -= speed;
                if (currentSize.y <= minSize.y) {
                    currentSize.y = minSize.y;
                    useAllCorners = true;
                }

            }


        }

        ImDrawCornerFlags cornerFlags = useAllCorners ? ImDrawCornerFlags_All : (ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_BotLeft);

        ImVec2 verticalMenuSize = ImVec2(currentSize.x, currentSize.y);
        draw::RectFilled(defaultBackgroundColor, menuPos, verticalMenuSize, cornerFlags, 7.5f);

        if (currentSize.y == maxSize.y && isMenuOpen) {
            if (horizontalCurrentWidth < optionSizeBox.x) {
                horizontalCurrentWidth += speed;
                if (horizontalCurrentWidth > optionSizeBox.x) {
                    horizontalCurrentWidth = optionSizeBox.x;
                }
            }
        }

        if (horizontalCurrentWidth > 0.0f) {
            ImVec2 horizontalMenuPos = ImVec2(menuPos.x, menuPos.y + maxSize.y);
            ImVec2 horizontalMenuSize = ImVec2(horizontalCurrentWidth, currentSize.x);
            //draw::RectFilled(defaultBackgroundColor, horizontalMenuPos, horizontalMenuSize, ImDrawCornerFlags_BotLeft | ImDrawCornerFlags_BotRight, 7.5f);
            draw::RectFilled(defaultBackgroundColor, { menuPos.x + currentSize.x, menuPos.y }, { horizontalMenuSize.x - mainMenuSize.x, verticalMenuSize.y }, ImDrawCornerFlags_TopRight | ImDrawCornerFlags_BotRight, 7.5f);
        }
    }

    bool Sub(std::string text) {
        subMenuOptionCount++;
        bool selecting = (subMenucurrentOptionCount == subMenuOptionCount);

        const float iconWidth = 45.f;
        const float iconHeight = 65.f;
        const float textOffsetX = 5.f;
        const float textOffsetYBase = 60.f;
        const float textOffsetYStart = 40.f;
        const int maxIconsPerColumn = 6;

        float yPos, xPos;

        float targetYPos = (textOffsetYBase * subMenuOptionCount) - textOffsetYStart;
        float startYPos = menuPos.y + (subMenuOptionCount - 1) * 10.f;
        yPos = (startYPos + (targetYPos - startYPos) * (currentSize.y / maxSize.y) + menuPos.y) + 3.5f;
        xPos = menuPos.x + textOffsetX;

        if (selecting && currentSize.y == minSize.y) {
            yPos = menuPos.y;
        }

        float alpha = std::clamp((currentSize.y - minSize.y) / (maxSize.y - minSize.y), 0.0f, 1.0f);
        ImVec2 textPos{ xPos, yPos };

        bool hoverMouse = false, held = false, pressed = false;
        ImVec4 iconColor = ImVec4(defaultTextColor.x, defaultTextColor.y, defaultTextColor.z, alpha);

        if (isMenuOpen) {
            pressed = control::MouseClick(text.c_str(), textPos, ImVec2(iconWidth, iconHeight), &hoverMouse, &held);
            draw::Text(text, hoverMouse ? textOnHoverColor : iconColor, textPos, m_font_icon);
        }

        if (pressed) {
            if (selecting && moveToTop) {
                isMenuOpen = true;
                moveToTop = false;
            }
            else {
                subMenucurrentOptionCount = subMenuOptionCount;
            }
        }

        return (hoverMouse && pressed);
    }

    void DrawHorizontalLine(ImVec4 color, ImVec2 startPos, float width, float thickness) {
        ImVec2 endPos = ImVec2(startPos.x + width, startPos.y);
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->AddLine(startPos, endPos, ImGui::ColorConvertFloat4ToU32(color), thickness);
    }

    void End() {
        int totalPages = (optionCount + maxOption - 1) / maxOption;
        int currentPage = (currentOption - 1) / maxOption + 1;

        float maxYPosition = (optionYOffset * maxOption + optionYStart + optionYOffset) + menuPos.y;
        ImVec2 textPos = { menuPos.x + optionXOffset + descriptionTextOffset.x, maxYPosition + 5.f };

        float fadeAlpha = std::clamp((currentSize.y - minSize.y) / (maxSize.y - minSize.y), 0.0f, 1.0f);
        ImVec4 fadedLineColor = ImVec4(bottomEndBoxColor2.x, bottomEndBoxColor2.y, bottomEndBoxColor2.z, fadeAlpha);
        ImVec4 fadedTextColor = ImVec4(textOnNormalColor.x, textOnNormalColor.y, textOnNormalColor.z, fadeAlpha);

        DrawHorizontalLine(fadedLineColor, { textPos.x + 5.f, textPos.y + 17.5f }, 400.f, 2.f);

        std::string pageCount = "Page " + std::to_string(currentPage) + "/" + std::to_string(totalPages);
        draw::Text(pageCount, fadedTextColor, ImVec2(textPos.x - rightSideTextOffet, textPos.y + 7.f), nullptr, true);
        draw::Text("Vehicle > " + subTitle, fadedTextColor, ImVec2(textPos.x, textPos.y + 7.f));
        draw::Text("v!.0.0", fadedTextColor, ImVec2((textPos.x - rightSideTextOffet) - 2.5f, textPos.y + 30.f), m_font_small, true);

    }




    namespace UIOptions
    {

        bool Button(const std::string option) {

            return DrawTextOnOption(option, "NULL", "NULL");

        }

        bool Int(const std::string& optionName, int& value, int min, int max, int step)
        {
            static bool blank = false;
            return DrawIntOption(optionName, value, min, max, step, false, blank);
        }

        bool Int(const std::string& optionName, int& value, int min, int max, int step, bool& toggle)
        {
            return DrawIntOption(optionName, value, min, max, step, true, toggle);
        }

        bool Float(const std::string& optionName, float& value, float min, float max, float step)
        {
            static bool blank = false;
            return DrawFloatOption(optionName, value, min, max, step, false, blank);
        }

        bool Float(const std::string& optionName, float& value, float min, float max, float step, bool& toggle)
        {
            return DrawFloatOption(optionName, value, min, max, step, true, toggle);
        }

        bool Toggle(const std::string& optionName, bool& toggle)
        {

            if (!isMenuOpen)
                return false;

            bool clikedOption = DrawTextOnOption(optionName, "NULL", toggle ? ICON_FA_TOGGLE_ON : ICON_FA_TOGGLE_OFF);


            //int startOption = (currentOption - 1) / maxOption * maxOption + 1;
            //int endOption = startOption + maxOption - 1;

            //if (optionCount >= startOption && optionCount <= endOption)
            //{

            //    float yPosition = (optionYOffset * (optionCount - startOption + 1) + optionYStart) + menuPos.y;
            //    ImVec2 textPos = ImVec2(menuPos.x, yPosition);
            //    ImVec2 sliderPos = ImVec2(textPos.x + optionSize.x + 35.f, textPos.y + 17.f);

            //    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, .5f));
            //    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 2));
            //    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
            //    ImGui::PushStyleColor(ImGuiCol_FrameBg, defaultBackgroundColor);
            //    ImGui::PushStyleColor(ImGuiCol_SliderGrab, textOnNormalColor);
            //    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.5f, 0.0f, 0.0f));

            //    ImGui::SetCursorScreenPos(sliderPos);

            //    if (ImGui::Checkbox(("##Toggle_" + optionName).c_str(), &toggle))
            //    {
            //        currentOption = optionCount;
            //    }
            //    ImGui::PopStyleColor(3);
            //    ImGui::PopStyleVar(3);

                if (clikedOption)
                {
                    toggle = !toggle;
                }
            //}
            return clikedOption;
        }

        bool StringArray(const std::string& optionName, std::vector<std::string>& options, int& currentIndex)
        {
            bool optionClicked = DrawTextOnOption(optionName, "NULL", "[" + options[currentIndex] + "]");
            bool selectedOption = (currentOption == optionCount);

            if (selectedOption) {
                if (control::leftPressed) {
                    currentIndex -= 1;
                    if (currentIndex < 0) currentIndex = options.size() - 1;
                    optionClicked = true;
                }
                if (control::rightPressed) {
                    currentIndex += 1;
                    if (currentIndex >= options.size()) currentIndex = 0;
                    optionClicked = true;
                }
            }


            return optionClicked;
        }



    }


    ImGuiWindowFlags menuWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollbar;
    ImVec2 menuWindowPos = ImVec2(0, 0);
    ImVec2 menuWindowSize = ImVec2(menuSize.x + 25.f, menuSize.y);
    ImVec4 menuWindowBgColor = ImVec4(0, 0, 0, 0);
    int inttest = 0;
    int inttest2 = 0;
    float Ftest = 0;
    bool testbool = true;
    bool testbool2 = true;
    float menuWindowBorderSize2 = 0.0f;
    float menuWindowBorderSize = 0.0f;
    bool setmenuPosOnScreen = true;
    std::vector<std::string> T = { "Option 1337" , "Option 1338", "Option 1339" };

    extern void DrawDebugMenu();

    void RenderMenu() {
        DrawDebugMenu();

        if (setmenuPosOnScreen)
            ImGui::SetNextWindowPos(menuWindowPos);
        setmenuPosOnScreen = false;

        ImGui::SetNextWindowSize(useSmallerWindow ? ImVec2(100.f, 100.f) : menuWindowSize);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, menuWindowBgColor);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, menuWindowBorderSize);

        control::ControlTick();
        subMenuOptionCount = 0;
        if (ImGui::Begin("SideUI", nullptr, menuWindowFlags)) {
            menuPos = ImGui::GetCursorScreenPos();

            DrawMainMenu();

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


            UIOptions::Button("Normal Button");
            UIOptions::Button("Normal Button");
            UIOptions::Toggle("Toggle Button", testbool2);
            UIOptions::Button("Normal Button");
            UIOptions::Int("Int Option", inttest, 0, 1000, 1);
            UIOptions::Toggle("Toggle Button", testbool2);
            UIOptions::Int("Int Option With Toggle", inttest, 0, 1000, 1, testbool2);
            UIOptions::Float("Float Option With Toggle", Ftest, 0, 1000, 1, testbool2);
            UIOptions::StringArray("String Array", T, inttest2);
            UIOptions::Button("Normal Button");
            UIOptions::Int("Int Option", inttest, 0, 1000, 1);
            UIOptions::Float("Float Option", Ftest, 0, 1000, 1);
            UIOptions::Button("Normal Button");
            UIOptions::Button("Normal Button");
            UIOptions::Button("Normal Button");
            UIOptions::Int("Int Option With Toggle", inttest, 0, 1000, 1, testbool2);
            UIOptions::Button("Normal Button");
            UIOptions::StringArray("String Array", T, inttest2);
            UIOptions::Button("Normal Button");
            UIOptions::Int("Int Option With Toggle", inttest, 0, 1000, 1, testbool2);
            UIOptions::Float("Float Option With Toggle", Ftest, 0, 1000, 1, testbool2);
            UIOptions::Button("Normal Button");
            UIOptions::Button("Normal Button");
            UIOptions::Button("Normal Button");
            UIOptions::Button("Normal Button");
            UIOptions::Button("Normal Button");
            UIOptions::Button("Normal Button");
   

            End();

            if (currentSize.y <= minSize.y)
                useSmallerWindow = true;

        }

        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        ImGui::End();
    }

    void DrawDebugMenu() {
        if (ImGui::Begin("Debug Menu")) {
            ImGui::Checkbox("Menu Open", &isMenuOpen);
            ImGui::Separator();
            ImGui::SliderFloat2("Menu Position", &menuPos.x, 0.0f, 1920.0f);
            ImGui::SliderInt("Max Options", &maxOption, 1, 61);
            ImGui::SliderFloat("Scroller Y", &scrollerY, 0.0f, 1000.0f);
            ImGui::SliderFloat("Scroller Speed", &scrollerSpeed, 0.01f, 5.0f);
            ImGui::SliderFloat("Start Y", &startY, 0.0f, 1000.0f);
            ImGui::SliderFloat("Option Y Offset", &optionYOffset, 0.0f, 100.0f);
            ImGui::SliderFloat("Option Y Start", &optionYStart, 0.0f, 200.0f);
            ImGui::SliderFloat("Header Offset X", &headerOffsetX, 0.0f, 50.0f);
            ImGui::SliderFloat("Right Side Text Offset", &rightSideTextOffet, 0.0f, 100.0f);
            ImGui::SliderFloat2("Option Size", &optionSize.x, 0.0f, 1000.0f);
            ImGui::SliderFloat2("Footer Size", &footerSize.x, 0.0f, 1000.0f);
            ImGui::SliderFloat2("Header Size", &headerSize.x, 0.0f, 1000.0f);
            ImGui::SliderFloat2("Description Text Offset", &descriptionTextOffset.x, 0.0f, 100.0f);
            ImGui::End();
        }
    }

}
