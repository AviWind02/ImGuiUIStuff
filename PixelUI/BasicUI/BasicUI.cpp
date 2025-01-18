#include "../common.h"
#include <functional>


namespace BsaicUI {

    // Global Variables
    std::string subTitle = "MainMenu";
    std::string textDescription = "description Box";
    ImVec2 menuPos = { 10, 40 };
    int maxOption = 10;
    float scrollerY = 0.0f; // The current Y position of the scroller
    float scrollerSpeed = 0.1f; // The speed of the scroller animation
    float startY = 0.0f; // The starting Y position of the scroller
    POINT lastMousePos = { 0, 0 };



    ImVec4 backDrop = ImVec4(1.f, 0.f, 1.f, 1.0f);




    // Colors
    ImVec4 defaultTextColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 defaultBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
    ImVec4 middleBoxBackColor = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    ImVec4 scrollBarColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    ImVec4 scrollBarColorClicked = ImVec4(1.f, 0.5f, 0.5f, 1.0f);
    ImVec4 textOnHoverColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 textOnNormalColor = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
    ImVec4 bottomEndBoxColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    ImVec4 bottomEndBoxColor2 = ImVec4(1.f, 1.f, 0.2f, 1.0f);
    //ImVec4 backDrop = ImVec4(1.f, 0.f, 1.f, 1.0f);

    // Window Sizes
    ImVec2 defaultDescriptionWindowSize = ImVec2(481, 153);
    ImVec2 defaultDescriptionWindowPos = ImVec2(1433, 856);

    // Positions and Sizes
    float optionYOffset = 25.0f;
    float optionYMouseOffset = 40.0f;
    float optionYStart = 75.0f;
    float headerOffsetX = 4.0f;
    float footerYPosition = 0.0f;
    float rightSideTextOffet = 4.f;

    ImVec2 optionSize = ImVec2(400, 25);
    ImVec2 footerSize = ImVec2(optionSize.x, optionSize.y);
    ImVec2 headerSize = ImVec2(optionSize.x, 60);
    ImVec2 descriptionTextOffset = ImVec2(10.0f, 2.5f);

    float headerBaseWidth = optionSize.x; // Total width available for headers
    float headerBaseOffsetX = headerOffsetX;
    float headerBaseOffsetY = 60.f;
    const int maxHeaders = 4; // Maximum number of headers
    float headerGrowthSpeed = 0.1f; // Speed factor for smooth growth




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


    bool DrawTextOnOption(const std::string& Ltext, const std::string Ctext, const std::string& Rtext)
    {
        optionCount++;


        bool hovered = false;
        bool held = false;

        int startOption = (currentOption - 1) / maxOption * maxOption + 1;
        int endOption = startOption + maxOption - 1;
        static int iconOffset;

        if (optionCount >= startOption && optionCount <= endOption)
        {
            float yPosition = (optionYOffset * (optionCount - startOption + 1) + optionYStart) + menuPos.y;
            ImVec2 textPos = ImVec2(menuPos.x - 4.0f, yPosition);

            static float smoothScrollYPosition = yPosition;
            float scrollSpeed = 0.1f;
            ImVec2 smoothTextPos = ImVec2(menuPos.x - 4.0f, smoothScrollYPosition);

            ImVec2 mousePos = ImGui::GetMousePos();
            ImVec2 optionEndPos = ImVec2(textPos.x + optionSize.x, (textPos.y + optionSize.y) - 5.f);

            bool clicked = (mousePos.x >= textPos.x && mousePos.x <= optionEndPos.x &&
                mousePos.y >= textPos.y && mousePos.y <= optionEndPos.y) &&
                ImGui::IsMouseClicked(ImGuiMouseButton_Left);

            hovered = (mousePos.x >= textPos.x && mousePos.x <= optionEndPos.x &&
                mousePos.y >= textPos.y && mousePos.y <= optionEndPos.y);

            if (clicked)
            {
                currentOption = optionCount;
            }

            bool selectedOption = (currentOption == optionCount);

            if (selectedOption) {
                smoothScrollYPosition += (yPosition - smoothScrollYPosition) * scrollSpeed;
            }



            //draw::RectFilled(middleBoxBackColor, textPos, optionSize);//Option Box - This is why when scrolling up it disappers

            if (hovered)
            {
                draw::RectFilled(scrollBarColor, textPos, optionSize, false);// Scroll bar for mouse
            }

            if (selectedOption)
            {
                draw::RectFilled(scrollBarColorClicked, smoothTextPos, optionSize, true);//Scroll bar for Selcted option
            }

            // Render the text
            draw::Text(Ltext, hovered ? textOnHoverColor : textOnNormalColor,
                { textPos.x + descriptionTextOffset.x, textPos.y + descriptionTextOffset.y });

            if (containsIcon(Rtext) || containsIcon(Ctext))
                iconOffset = 3.f;

            if (Rtext != "NULL")
            {
                draw::Text(Rtext, hovered ? textOnHoverColor : textOnNormalColor,
                    { (textPos.x + descriptionTextOffset.x) - rightSideTextOffet, (textPos.y + descriptionTextOffset.y) + iconOffset },
                    nullptr, true);
            }

            if (Ctext != "NULL")
            {
                draw::Text(Ctext, hovered ? textOnHoverColor : textOnNormalColor,
                    { (textPos.x + descriptionTextOffset.x) - rightSideTextOffet, (textPos.y + descriptionTextOffset.y) + iconOffset },
                    nullptr, false, true);
            }

            // Handle the selection logic
            if (selectedOption && (clicked || held || control::selectPressed))
            {
                control::selectPressed = false;
                return true;
            }
        }

        return false;
    }

    int headerCount = 3;
    int pickedIndex;
    void HoverableRectangleWithText(std::string option, int index)
    {
        float currentWidth = headerBaseWidth / headerCount;

        ImVec2 minSize = { currentWidth, optionSize.y };    // Size when not hovering
        ImVec2 maxSize = { currentWidth, 40 };              // Size when fully hovered

        static ImVec2 currentSize[maxHeaders];
        static bool initialized[maxHeaders] = { false };
        static bool hovered[maxHeaders] = { false };
        static bool held[maxHeaders] = { false };

        // Initialize the size if not done yet
        if (!initialized[index])
        {
            currentSize[index] = minSize;
            initialized[index] = true;
        }

        ImVec2 rectPos = { (menuPos.x + index * currentWidth) - headerBaseOffsetX, menuPos.y + headerBaseOffsetY };
        ImVec2 frontRectSize = { currentWidth, 5.f };
        ImVec2 frontRectPos = { (menuPos.x + index * currentWidth) - headerBaseOffsetX, (menuPos.y + optionSize.y) + headerBaseOffsetY };

        ImVec4 textColor = textOnNormalColor;
        float textHoverOffsetY = .0f;

        if (control::MouseClick("Rect" + std::to_string(index), rectPos, currentSize[index], &hovered[index], &held[index]))
        {
            pickedIndex = index;
        }

        // Smoothly interpolate the size based on hover state
        if (hovered[index] || pickedIndex == index)
        {
            // Smoothly increase size towards the maximum size
            currentSize[index].y = ImLerp(currentSize[index].y, maxSize.y, headerGrowthSpeed);
            textColor = textOnHoverColor; // Change text color on hover
        }
        else
        {
            // Smoothly decrease size back towards the minimum size
            currentSize[index].y = ImLerp(currentSize[index].y, minSize.y, headerGrowthSpeed);
        }

        // Adjust rectPos.y to grow upwards as currentSize[index].y increases
        rectPos.y -= (currentSize[index].y - minSize.y) * 0.5f; // Smooth position adjustment for growth

        // Draw the stationary front rectangle
        draw::RectFilled(defaultBackgroundColor, frontRectPos, frontRectSize);

        // Draw the growing rectangle behind the front rectangle
        draw::RectFilled(middleBoxBackColor, rectPos, currentSize[index]);

        draw::Line(bottomEndBoxColor2, frontRectPos, { 0, 0 }, 1.f);
        // Calculate the position for the text, so it rises with the growing rectangle
        ImVec2 textPos = rectPos;
        textPos.x += (currentSize[index].x / 2) - (ImGui::CalcTextSize(option.c_str()).x / 2); // Center the text horizontally

        // Adjust text position vertically
        if (hovered[index])
        {
            textPos.y += (currentSize[index].y / 2) - (ImGui::CalcTextSize(option.c_str()).y / 2) + textHoverOffsetY; // Lower the text on hover
        }
        else
        {
            textPos.y += (currentSize[index].y / 2) - (ImGui::CalcTextSize(option.c_str()).y / 2); // Center the text vertically
        }

        // Draw the text
        draw::Text(option, textColor, { textPos.x - 20.f, textPos.y }, m_font_big, false);
    }


    void Title(const std::string& text)
    {
        std::string textTitle = "PROJECT PIXEL";
        ImGui::PushFont(m_font_title);
        float fontSize = ImGui::GetFontSize() * textTitle.size() / 2;
        ImGui::PopFont();
        ImVec2 textPos = { (ImGui::GetWindowSize().x / 2 - fontSize + (fontSize / 2)) + menuPos.x, (menuPos.y + 10.f) };
        draw::RectFilled(bottomEndBoxColor, ImVec2(menuPos.x - headerOffsetX, menuPos.y), headerSize);
        draw::Text(textTitle, textOnNormalColor, textPos, m_font_title);
    }

    void End()
    {
        int totalPages = (optionCount + maxOption - 1) / maxOption; // Round up to the nearest page
        int currentPage = (currentOption - 1) / maxOption + 1;

        int startOption = (currentPage - 1) * maxOption + 1;
        int displayedOptions = optionCount - startOption + 1;
        displayedOptions = (displayedOptions > maxOption) ? maxOption : displayedOptions;

        float targetYPosition = (optionYOffset * displayedOptions + optionYStart + optionYOffset) + menuPos.y;

        static float currentYPosition = targetYPosition;
        float speed = .1f;
        currentYPosition += (targetYPosition - currentYPosition) * speed;

        ImVec2 textPos = { menuPos.x + 6.f, currentYPosition };

        draw::RectFilled(bottomEndBoxColor, ImVec2(textPos.x - 10.0f, textPos.y - .3f), footerSize);
        std::string pageCount = "Page " + std::to_string(currentPage) + "/" + std::to_string(totalPages);
        draw::Text(pageCount, textOnNormalColor, ImVec2(textPos.x - rightSideTextOffet, textPos.y + 5.f), nullptr, true);
        draw::Text("vDEV | Atlas | " + subTitle, textOnNormalColor, ImVec2(textPos.x, textPos.y + 2.f));
    }
    void DrawBackdrop()
    {
        ImVec2 backdropPos = ImVec2(menuPos.x - 4.0f, menuPos.y);

        int startOption = (currentOption - 1) / maxOption * maxOption + 1;
        int displayedOptions = optionCount - startOption + 1;
        displayedOptions = (displayedOptions > maxOption) ? maxOption : displayedOptions;

        float backdropHeight = ((optionYOffset * displayedOptions) + optionYStart) + 50.f;

        ImVec2 backdropSize = ImVec2(optionSize.x + 8.0f, backdropHeight);

       
        draw::RectFilled(middleBoxBackColor, backdropPos, backdropSize);

        optionCount = 0;
    }

    bool DrawIntOption(const std::string& optionName, int& value, int min, int max, int step, bool useToggle, bool& toggle) {

        bool optionClicked = DrawTextOnOption(optionName, "NULL", "NULL");
        bool selectedOption = (currentOption == optionCount);
        bool toggleChanged = false;
        bool valueChanged = false;

        int startOption = (currentOption - 1) / maxOption * maxOption + 1;
        int endOption = startOption + maxOption - 1;

        if (optionCount >= startOption && optionCount <= endOption)
        {

            float yPosition = (optionYOffset * (optionCount - startOption + 1) + optionYStart) + menuPos.y;
            ImVec2 textPos = ImVec2(menuPos.x, yPosition);

            // Calculate text width
            ImVec2 textSize = ImGui::CalcTextSize(optionName.c_str());
            float textWidth = textSize.x;

            // Default slider width and position
            float defaultSliderWidth = useToggle ? 152.5f : 181.f;
            float sliderWidth = defaultSliderWidth;
            ImVec2 sliderPos = ImVec2(textPos.x + optionSize.x - 200.f, textPos.y + 17.f);

            // Adjust the slider width and position if the text is too long
            float maxTextWidth = 150.0f; // Max width before we start adjusting
            if (textWidth > maxTextWidth) {
                float overflow = textWidth - maxTextWidth;
                sliderWidth -= overflow; // Reduce the slider width based on the overflow
                if (sliderWidth < 50.0f) { // Ensure a minimum slider width
                    sliderWidth = 50.0f;
                }
                sliderPos.x += overflow; // Shift the slider to the right
            }

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, .5f));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 1));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
            ImGui::PushStyleColor(ImGuiCol_FrameBg, defaultBackgroundColor);
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, textOnNormalColor);
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.5f, 0.0f, 0.0f));


            ImGui::SetCursorScreenPos(sliderPos);
            ImGui::PushItemWidth(sliderWidth);
            valueChanged = ImGui::SliderInt(("##" + optionName).c_str(), &value, min, max);

            if (useToggle)
            {
                ImGui::SameLine(0.f);
                toggleChanged = ImGui::Checkbox(("##Toggle_" + optionName).c_str(), &toggle);
            }

            if (valueChanged || toggleChanged)
                currentOption = optionCount;
            ImGui::PopItemWidth();

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

        bool optionClicked = DrawTextOnOption(optionName, "NULL", "NULL");
        bool selectedOption = (currentOption == optionCount);
        bool toggleChanged = false;
        bool valueChanged = false;




        int startOption = (currentOption - 1) / maxOption * maxOption + 1;
        int endOption = startOption + maxOption - 1;

        if (optionCount >= startOption && optionCount <= endOption)
        {


            float yPosition = (optionYOffset * (optionCount - startOption + 1) + optionYStart) + menuPos.y;
            ImVec2 textPos = ImVec2(menuPos.x, yPosition);

            // Calculate text width
            ImVec2 textSize = ImGui::CalcTextSize(optionName.c_str());
            float textWidth = textSize.x;

            // Default slider width and position
            float defaultSliderWidth = useToggle ? 152.5f : 181.f;
            float sliderWidth = defaultSliderWidth;
            ImVec2 sliderPos = ImVec2(textPos.x + optionSize.x - 200.f, textPos.y + 17.f);

            // Adjust the slider width and position if the text is too long
            float maxTextWidth = 150.0f; // Max width before we start adjusting
            if (textWidth > maxTextWidth) {
                float overflow = textWidth - maxTextWidth;
                sliderWidth -= overflow; // Reduce the slider width based on the overflow
                if (sliderWidth < 50.0f) { // Ensure a minimum slider width
                    sliderWidth = 50.0f;
                }
                sliderPos.x += overflow; // Shift the slider to the right
            }

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, .5f));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 2));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
            ImGui::PushStyleColor(ImGuiCol_FrameBg, defaultBackgroundColor);
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, textOnNormalColor);
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.5f, 0.0f, 0.0f));


            ImGui::SetCursorScreenPos(sliderPos);
            ImGui::PushItemWidth(sliderWidth);
            valueChanged = ImGui::SliderFloat(("##" + optionName).c_str(), &value, min, max);

            if (useToggle)
            {
                ImGui::SameLine(0.f);
                toggleChanged = ImGui::Checkbox(("##Toggle_" + optionName).c_str(), &toggle);
            }

            if (valueChanged || toggleChanged)
                currentOption = optionCount;
            ImGui::PopItemWidth();

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
            bool clikedOption = DrawTextOnOption(optionName, "NULL", "NULL");


            int startOption = (currentOption - 1) / maxOption * maxOption + 1;
            int endOption = startOption + maxOption - 1;

            if (optionCount >= startOption && optionCount <= endOption)
            {

                float yPosition = (optionYOffset * (optionCount - startOption + 1) + optionYStart) + menuPos.y;
                ImVec2 textPos = ImVec2(menuPos.x, yPosition);
                ImVec2 sliderPos = ImVec2(textPos.x + optionSize.x - 40.f, textPos.y + 17.f);

                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, .5f));
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 2));
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
                ImGui::PushStyleColor(ImGuiCol_FrameBg, defaultBackgroundColor);
                ImGui::PushStyleColor(ImGuiCol_SliderGrab, textOnNormalColor);
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.5f, 0.0f, 0.0f));

                ImGui::SetCursorScreenPos(sliderPos);

                if (ImGui::Checkbox(("##Toggle_" + optionName).c_str(), &toggle))
                {
                    currentOption = optionCount;
                }
                ImGui::PopStyleColor(3);
                ImGui::PopStyleVar(3);

                if (clikedOption)
                {
                    toggle = !toggle;
                }
            }
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


    // Window Flags
    ImGuiWindowFlags menuWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollbar;
    ImVec2 menuWindowPos = ImVec2(0, 0);
    ImVec2 menuWindowSize = ImVec2(400, 600);
    ImVec4 menuWindowBgColor = ImVec4(0, 0, 0, 0);
    float menuWindowBorderSize = 0.0f;
    int inttest = 0;
    int inttest2 = 0;
    float Ftest = 0;
    bool testbool = true;
    bool testbool44 = true;
    bool testbool2 = true;
    std::vector<std::string> T = { "Option 1337" , "Option 1338", "Option 1339" };
    extern void Debug();
    void RenderMenu()
    {
        Debug();
        if (testbool)
            ImGui::SetNextWindowPos(menuWindowPos);
        testbool = false;


        ImGui::SetNextWindowSize(menuWindowSize);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, menuWindowBgColor);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, menuWindowBorderSize);

        control::ControlTick();
        if (ImGui::Begin("BsaicUI", nullptr, menuWindowFlags))
        {
            DrawBackdrop();

            menuPos = ImGui::GetCursorScreenPos();
            Title("Title");

            HoverableRectangleWithText("Local", 0);
            HoverableRectangleWithText("Vehicle", 1);
            HoverableRectangleWithText("Network", 2);


            DrawTextOnOption("Sub Option", "NULL", ICON_FA_ARROW_RIGHT);
    






            End();

        }

        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        ImGui::End();
    }


    void Debug()
    {
        ImGui::Begin("Debug Menu", &testbool44);

        // Adjust Window Sizes
        ImGui::SliderFloat2("Description Window Size", (float*)&defaultDescriptionWindowSize, 0.0f, 1000.0f);
        ImGui::SliderFloat2("Description Window Position", (float*)&defaultDescriptionWindowPos, 0.0f, 2000.0f);

        // Adjust Positions and Sizes
        ImGui::SliderFloat("Option Y Offset", &optionYOffset, 0.0f, 100.0f);
        ImGui::SliderFloat("Option Y Mouse Offset", &optionYMouseOffset, 0.0f, 100.0f);
        ImGui::SliderFloat("Option Y Start", &optionYStart, 0.0f, 200.0f);
        ImGui::SliderFloat("Header Offset X", &headerOffsetX, 0.0f, 100.0f);
        ImGui::SliderFloat("Footer Y Position", &footerYPosition, 0.0f, 200.0f);
        ImGui::SliderFloat("Right Side Text Offset", &rightSideTextOffet, 0.0f, 100.0f);

        ImGui::SliderFloat2("Option Size", (float*)&optionSize, 0.0f, 800.0f);
        ImGui::SliderFloat2("Footer Size", (float*)&footerSize, 0.0f, 800.0f);
        ImGui::SliderFloat2("Header Size", (float*)&headerSize, 0.0f, 800.0f);
        ImGui::SliderFloat2("Description Text Offset", (float*)&descriptionTextOffset, 0.0f, 100.0f);

        ImGui::SliderFloat("Header Base Width", &headerBaseWidth, 0.0f, 800.0f);
        ImGui::SliderFloat("Header Base Offset X", &headerBaseOffsetX, 0.0f, 100.0f);
        ImGui::SliderFloat("Header Base Offset Y", &headerBaseOffsetY, 0.0f, 200.0f);
        ImGui::SliderFloat("Header Growth Speed", &headerGrowthSpeed, 0.0f, 1.0f);

        // Adjust Menu Positions
        ImGui::SliderFloat2("Menu Position", (float*)&menuPos, 0.0f, 2000.0f);
        ImGui::SliderInt("Max Option", &maxOption, 1, 100);
        ImGui::SliderFloat("Scroller Y", &scrollerY, 0.0f, 1000.0f);
        ImGui::SliderFloat("Scroller Speed", &scrollerSpeed, 0.0f, 1.0f);
        ImGui::SliderFloat("Start Y", &startY, 0.0f, 1000.0f);

        // Display Mouse Position (read-only)
        ImGui::Text("Last Mouse Position: (%d, %d)", lastMousePos.x, lastMousePos.y);

        ImGui::End();
    }


}