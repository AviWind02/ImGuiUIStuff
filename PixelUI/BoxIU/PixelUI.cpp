#include "../common.h"


// Global Variables
std::string subTitle = "MainMenu";
std::string textDescription = "description Box";
ImVec2 MenuPos = { 10, 15 };
int optionCount = 0;
int trackedOptionCount = 0;
int currentOption = 0;
int maxOption = 10;
float scrollerY = 0.0f; // The current Y position of the scroller
float scrollerSpeed = 0.1f; // The speed of the scroller animation
float startY = 0.0f; // The starting Y position of the scroller
POINT lastMousePos = { 0, 0 };


// Font
extern ImFont* m_font_big;



// Colors
ImVec4 defaultTextColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
ImVec4 defaultBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
ImVec4 middleBoxBackColor = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
ImVec4 scrollBarColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
ImVec4 scrollBarColorClicked = ImVec4(1.f, 0.5f, 0.5f, 1.0f);
ImVec4 textOnHoverColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
ImVec4 textOnNormalColor = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
ImVec4 bottomEndBoxColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

// Window Sizes
ImVec2 defaultDescriptionWindowSize = ImVec2(481, 153);
ImVec2 defaultDescriptionWindowPos = ImVec2(1433, 856);

// Positions and Sizes
float optionYOffset = 25.0f;
float optionYStart = 55.0f;
float headerOffsetX = 4.0f;
float footerYPosition = 0.0f;

ImVec2 optionSize = ImVec2(400, 25);
ImVec2 footerSize = ImVec2(400, 25);
ImVec2 headerSize = ImVec2(400, 80);
ImVec2 descriptionTextOffset = ImVec2(10.0f, 5.0f);




//Sub Menu Stuff
enum SubMenu {
    MainMenu,
    LocalMenu_SUB,
    ClothingMenu_SUB,
};
static constexpr int MaxSubMenuLevels = 1000;
SubMenu subMenuArray[MaxSubMenuLevels];
int subMenuLevel = 0;
SubMenu currentSubMenu = MainMenu;

void NextSubmenu(SubMenu menu) {
    if (subMenuLevel < MaxSubMenuLevels) {
        subMenuArray[subMenuLevel] = currentSubMenu;
        subMenuLevel++;
        currentSubMenu = menu;
        currentOption = 1;
    }
}
void BackSubmenu() {
    if (subMenuLevel > 0) {
        subMenuLevel--;
        currentSubMenu = subMenuArray[subMenuLevel];
        currentOption = 1;  // Assuming currentOption is defined elsewhere
    }
}





void DescriptionBox(const std::string& text)
{
    static ImVec2 descriptionWindowPos = defaultDescriptionWindowPos;
    static ImVec4 descriptionBackgroundColor = defaultBackgroundColor;
    static ImVec4 descriptionTextColor = defaultTextColor;

    //Set a max width for wrapping
    float wrapWidth = 300.0f;

    //Calculate the size of the window based on the text length with wrapping
    ImVec2 textSize = ImGui::CalcTextSize(text.c_str(), nullptr, false, wrapWidth);
    ImVec2 descriptionWindowSize = ImVec2(wrapWidth + 20.0f, textSize.y + 20.0f); //Add some padding

    //Get the current cursor position
    ImVec2 cursorPos = ImGui::GetMousePos();

    //Set the window position based on cursor visibility
    if (control::cursorVisible)
    {
        ImGui::SetNextWindowPos({ cursorPos.x + 15, cursorPos.y + 5 });
        ImGui::SetNextWindowSize(descriptionWindowSize);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, descriptionBackgroundColor);

        //Create the window
        if (ImGui::Begin("Description", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar))
        {
            ImGui::PushTextWrapPos(ImGui::GetCursorPosX() + wrapWidth);
            ImGui::TextWrapped("%s", text.c_str());
            ImGui::PopTextWrapPos();
        }

        ImGui::PopStyleColor();
        ImGui::End();
    }
}

void DescriptionBox()
{
    if (!control::cursorVisible)
    {
        int opCount = (optionCount > maxOption) ? (maxOption + 2) : (optionCount + 2);
        float yPosition = 25.0f * opCount + 65.0f;
        ImVec2 textPos = { ImGui::GetCursorScreenPos().x + 10.0f, yPosition };

        //Calculate the size of the text with wrapping
        ImVec2 textSize = ImGui::CalcTextSize(textDescription.c_str(), nullptr, false, footerSize.x - 20.0f);

        //Adjust the height of the footer based on the text height
        ImVec2 adjustedFooterSize = footerSize;
        adjustedFooterSize.y = textSize.y + 10.0f;

        //Draw the background rectangle
        draw::RectFilled(bottomEndBoxColor, ImVec2(textPos.x - 14.0f, textPos.y - 5.0f), adjustedFooterSize);

        //Render the wrapped text
        ImGui::SetCursorScreenPos(ImVec2(textPos.x, textPos.y + 13.f));
        ImGui::PushStyleColor(ImGuiCol_Text, textOnNormalColor);
        ImGui::PushTextWrapPos(textPos.x + footerSize.x - 20.0f);
        ImGui::TextWrapped(textDescription.c_str());
        ImGui::PopTextWrapPos();
        ImGui::PopStyleColor();
    }
}




bool setOption(const std::string& Ltext, const std::string& Rtext, const std::string& descriptionText)
{
    optionCount++;

    bool hovered = false;
    bool held = false;
    bool isHovered = false;
    bool clicked = control::MouseClickOption(Ltext, &hovered, &held);
    bool selectedOption = (clicked || (currentOption == optionCount));
    control::cursorVisible ? isHovered = hovered : isHovered = (currentOption == optionCount);
    

    if (isHovered) {

        if (control::cursorVisible) {
            DescriptionBox(descriptionText);
        }
        else {
            textDescription = descriptionText;
        }
    }

    if (currentOption <= maxOption && optionCount <= maxOption)
    {
        float yPosition = optionYOffset * optionCount + optionYStart;

        ImVec2 textPos = ImVec2(ImGui::GetCursorScreenPos().x - 4.0f, yPosition);

        draw::RectFilled(middleBoxBackColor, textPos, optionSize);
        if (isHovered)
        {
            draw::RectFilled(scrollBarColor, textPos, optionSize, false);
            if (selectedOption)
            {
                draw::RectFilled(scrollBarColorClicked, textPos, optionSize, true);
            }
        }
        draw::Text(Ltext, isHovered ? textOnHoverColor : textOnNormalColor, { textPos.x + descriptionTextOffset.x, textPos.y + descriptionTextOffset.y });
        if (Rtext != "NULL")
            draw::Text(Rtext, isHovered ? textOnHoverColor : textOnNormalColor, { textPos.x + descriptionTextOffset.x, textPos.y + descriptionTextOffset.y }, nullptr, true);

    }
    else if (optionCount > (currentOption - maxOption) && optionCount <= currentOption)
    {
        float yPosition = optionYOffset * (optionCount - (currentOption - maxOption)) + 55.0f;
        ImVec2 textPos = ImVec2(ImGui::GetCursorScreenPos().x - 4.0f, yPosition);

        draw::RectFilled(middleBoxBackColor, textPos, optionSize);
        if (isHovered)
        {
            draw::RectFilled(scrollBarColor, textPos, optionSize, false);
            if (selectedOption)
            {
                draw::RectFilled(scrollBarColorClicked, textPos, optionSize, true);
            }
        }
        draw::Text(Ltext, isHovered ? textOnHoverColor : textOnNormalColor, { textPos.x + descriptionTextOffset.x, textPos.y + descriptionTextOffset.y });
        if (Rtext != "NULL")
             draw::Text(Rtext, isHovered ? textOnHoverColor : textOnNormalColor, { textPos.x + descriptionTextOffset.x, textPos.y + descriptionTextOffset.y }, nullptr, true);
    }

    if (selectedOption && (control::selectPressed || held))
    {
        control::selectPressed = false;
        return true;
    }
    return false;
}

namespace UIOptions
{
    bool Button(const std::string& text, const std::string& descriptionText)
    {
        return setOption(text, "NULL", descriptionText);
    }

    bool Int(const std::string& text, int& value, int minValue, int maxValue, int step, const std::string& descriptionText)
    {
        std::string Rtext = "[" + std::to_string(value) + "/" + std::to_string(maxValue) + "]";
        bool cliked = setOption(text, Rtext, descriptionText);

        if (currentOption == optionCount)
        {
            if (control::rightPressed)
            {
                value += step;
                if (value > maxValue) value = minValue;  // Wrap to min
                return true;
            }
            else if (control::leftPressed)
            {
                value -= step;
                if (value < minValue) value = maxValue;  // Wrap to max
                return true;
            }
            return cliked;
        }
        return false;
    }

    bool Float(const std::string& text, float& value, float minValue, float maxValue, float step, int precision, const std::string& descriptionText)
    {
        std::string Rtext = "[" + draw::FormatFloat(value, precision) + "/" + draw::FormatFloat(maxValue, precision) + "]";
        bool cliked = setOption(text, Rtext, descriptionText);

        if (currentOption == optionCount)
        {
            if (control::rightPressed)
            {
                value += step;
                if (value > maxValue) value = minValue;  // Wrap to min
                return true;
            }
            else if (control::leftPressed)
            {
                value -= step;
                if (value < minValue) value = maxValue;  // Wrap to max
                return true;
            }
            return cliked;
        }
        return false;
    }

    bool Toggle(const std::string& text, bool& value, const std::string& descriptionText)
    {
        std::string Rtext = value ? ICON_FA_TOGGLE_ON : ICON_FA_TOGGLE_OFF;
        bool cliked = setOption(text, Rtext, descriptionText);

        if (cliked)
        {
            value = !value;
            return true;
        }
        return false;
    }

    bool Sub(const std::string& text, bool& value, SubMenu menu, const std::string& descriptionText)
    {
        bool cliked = setOption(text, ICON_FA_ARROW_CIRCLE_RIGHT, descriptionText);
        if (cliked)
        {
            NextSubmenu(menu);
            return true;
        }
        return false;
    }

    bool StringArray(const std::string& text, int& currentIndex, const std::vector<std::string>& options, const std::string& descriptionText)
    {
        if (options.empty())
            return false;

        std::string Rtext = "[" + options[currentIndex] + "]";
        bool cliked = setOption(text, Rtext, descriptionText);

        if (currentOption == optionCount)
        {
            if (control::rightPressed)
            {
                currentIndex = (currentIndex + 1) % options.size();
                return true;
            }
            else if (control::leftPressed)
            {
                currentIndex = (currentIndex - 1 + options.size()) % options.size();
                return true;
            }
            return cliked;
        }
        return false;
    }

}

void Title(const std::string& text)
{
    std::string textTitle = "Pixel";
    ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();
    ImGui::PushFont(m_font_title);
    float fontSize = ImGui::GetFontSize() * textTitle.size() / 2;
    ImGui::PopFont();
    ImVec2 textPos = { ImGui::GetWindowSize().x / 2 - fontSize + (fontSize / 2), 20.0f };

    draw::RectFilled(bottomEndBoxColor, ImVec2(cursorScreenPos.x - headerOffsetX, 0.0f), headerSize);
    draw::Text(textTitle, textOnNormalColor, textPos, m_font_title);
    subTitle = text;
}

void End()
{
    
    int opCount = (optionCount > maxOption) ? (maxOption + 1) : (optionCount + 1);
    std::string count = (std::to_string(currentOption) + "/" + std::to_string(optionCount)).c_str();
    float yPosition = 25.0f * opCount + 60.0f;
    ImVec2 textPos = { ImGui::GetCursorScreenPos().x + 10.0f, yPosition };
    draw::RectFilled(bottomEndBoxColor, ImVec2(textPos.x - 14.0f, textPos.y - 4.5f), footerSize);
    draw::Text(count, textOnNormalColor, ImVec2(textPos.x, textPos.y - 1.5f), nullptr, true);
    draw::Text("vBETA | Pixel | " + subTitle, textOnNormalColor, ImVec2(textPos.x, textPos.y - 1.5f));
    DescriptionBox();
}




// Window Flags
ImGuiWindowFlags menuWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollbar;
ImVec2 menuWindowPos = ImVec2(0, 0);
ImVec2 menuWindowSize = ImVec2(400, 520);
ImVec4 menuWindowBgColor = ImVec4(0, 0, 0, 0);
float menuWindowBorderSize = 0.0f;
int inttest = 0;
bool testbool;
std::vector<std::string> T = { "Option 1337" };
void RenderMenu()
{
    ImGui::SetNextWindowPos(menuWindowPos);
    ImGui::SetNextWindowSize(menuWindowSize);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, menuWindowBgColor);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, menuWindowBorderSize);

    control::ControlTick();

    if (ImGui::Begin("MenuWindow", nullptr, menuWindowFlags))
    {
        // Render Menu
        Title("Title");
        if (UIOptions::Button("Basic Option", "Option"))
        {
            std::cout << "Hey" << std::endl;
        }
        UIOptions::Int("Int Option", inttest, 0, 1000, 100, "Init");
        UIOptions::Float("Float Option", menuWindowBorderSize, 0, 1000, 1.3, 1, "Float");
        UIOptions::Toggle("Toggle Option", testbool, "Toggle");
        UIOptions::Sub("Sub Option", testbool, MainMenu, "Sub Menu");
        UIOptions::StringArray("Array Option", inttest, T, "String Array Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");
        UIOptions::Button("Option 2", "Option");


        End();

    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::End();
}




//ICON_FA_ARROW_CIRCLE_RIGHT This one
//ICON_FA_ARROW_RIGHT
//ICON_FA_ARROW_ALT_CIRCLE_RIGHT
//ICON_FA_GRIP_LINES
//ICON_FA_LAYER_GROUP