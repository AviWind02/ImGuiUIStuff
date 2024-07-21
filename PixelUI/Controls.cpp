#include"common.h"
namespace control
{

    // Key press delay and other variables
    int keyPressDelay = 150;
    int maxOptionForTop = 3;
    uint64_t keyPressDelayTickCount = GetTickCount64();

    // Menu state variables
    bool leftPressed = false;
    bool rightPressed = false;
    bool selectPressed = false;
    bool isMenuOpen = true;
    bool isMouseEnabled = true;
    bool cursorVisible = true;

    bool IsKeyPressed(int virtualKey)
    {
        return GetAsyncKeyState(virtualKey) & 0x8000;
    }

    bool Forward() { return IsKeyPressed('W'); }
    bool ShiftL() { return IsKeyPressed(VK_LSHIFT); }
    bool Backward() { return IsKeyPressed('S'); }
    bool RightSideward() { return IsKeyPressed('D'); }
    bool LeftSideward() { return IsKeyPressed('A'); }
    bool OpenKey() { return IsKeyPressed(VK_F4); }
    bool MouseKey() { return IsKeyPressed('X'); }
    bool FavKey() { return IsKeyPressed('B'); }
    bool ScrollTopMenu() { return IsKeyPressed(VK_INSERT); }
    bool UpKey() { return IsKeyPressed(VK_UP) || IsKeyPressed(VK_NUMPAD8); }
    bool ScrollUp() { return ImGui::GetIO().MouseWheel == 1; }
    bool ScrollDown() { return ImGui::GetIO().MouseWheel == -1; }
    bool DownKey() { return IsKeyPressed(VK_DOWN) || IsKeyPressed(VK_NUMPAD2); }
    bool RightKey() { return IsKeyPressed(VK_RIGHT) || IsKeyPressed(VK_NUMPAD6); }
    bool LeftKey() { return IsKeyPressed(VK_LEFT) || IsKeyPressed(VK_NUMPAD4); }
    bool SelectKey() { return IsKeyPressed(VK_RETURN) || IsKeyPressed(VK_NUMPAD5); }
    bool BackKey() { return IsKeyPressed(VK_BACK) || IsKeyPressed(VK_NUMPAD0); }

    void ToggleMouseCursorVisibility()
    {
        if (GetAsyncKeyState('X') & 0x8000)
        {
            if (cursorVisible)
            {
                ShowCursor(FALSE); // Hide the cursor
                cursorVisible = false;
            }
            else
            {
                ShowCursor(TRUE); // Show the cursor
                cursorVisible = true;
            }

            // To avoid rapid toggling, wait until the key is released
            while (GetAsyncKeyState('X') & 0x8000) {}
        }
    }

    void ToggleMouseCursorVisibilityOnClick()
    {
        ShowCursor(FALSE); 
        cursorVisible = false;
    }

    // Mouse click function
    bool MouseClick(const std::string& text, ImVec2 pos, ImVec2 size, bool* out_hovered, bool* out_held)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        const ImGuiID id = window->GetID(text.c_str());
        const ImRect bb(pos, draw::Add(pos, size));
        return ImGui::ButtonBehavior(bb, id, out_hovered, out_held);
    }

    bool MouseClickOption(const std::string& text, bool* out_hovered, bool* out_held)
    {
        if (optionCount <= maxOption && currentOption <= maxOption)
        {
            float yPosition = optionYOffset * optionCount + optionYStart;
            ImVec2 textPos = ImVec2(ImGui::GetCursorScreenPos().x - 4.0f, yPosition);
            return MouseClick(text, textPos, { optionSize.x - 25.0f, optionSize.y }, out_hovered, out_held);
        }
        else if (optionCount > (currentOption - maxOption) && optionCount <= currentOption)
        {
            float yPosition = optionYOffset * (optionCount - (currentOption - maxOption)) + 5.0f;
            ImVec2 textPos = ImVec2(ImGui::GetCursorScreenPos().x - 4.0f, yPosition);
            return MouseClick(text, textPos, { optionSize.x - 25.0f, optionSize.y }, out_hovered, out_held);
        }
        return false;
    }


    void ControlTick()
    {
        uint64_t currentTick = GetTickCount64();

        if (currentTick - keyPressDelayTickCount > keyPressDelay)
        {
            if (OpenKey())
            {
                isMenuOpen = !isMenuOpen;
                keyPressDelayTickCount = currentTick;
            }
            else if (MouseKey())
            {
                isMouseEnabled = !isMouseEnabled;
                keyPressDelayTickCount = currentTick;
            }
        }

        if (isMenuOpen)
        {
            rightPressed = false;
            leftPressed = false;
            selectPressed = false;

            if (currentTick - keyPressDelayTickCount > 50)
            {
                if (ScrollUp())
                {
                    currentOption > 1 ? currentOption-- : currentOption = optionCount;
                    keyPressDelayTickCount = currentTick;
                }
                else if (ScrollDown())
                {
                    currentOption < optionCount ? currentOption++ : currentOption = 1;
                    keyPressDelayTickCount = currentTick;
                }
            }

            if (currentTick - keyPressDelayTickCount > keyPressDelay)
            {
                if (UpKey())
                {
                    ToggleMouseCursorVisibilityOnClick();
                    currentOption > 1 ? currentOption-- : currentOption = optionCount;
                    keyPressDelayTickCount = currentTick;
                }
                else if (DownKey())
                {
                    ToggleMouseCursorVisibilityOnClick();
                    currentOption < optionCount ? currentOption++ : currentOption = 1;
                    keyPressDelayTickCount = currentTick;
                }
                else if (SelectKey())
                {
                    selectPressed = true;
                    keyPressDelayTickCount = currentTick;
                }
                else if (BackKey())
                {
                    ToggleMouseCursorVisibilityOnClick();
                    // BackSubmenu();
                    keyPressDelayTickCount = currentTick;
                }
                else if (RightKey())
                {
                    ToggleMouseCursorVisibilityOnClick();
                    rightPressed = true;
                    keyPressDelayTickCount = currentTick;
                }
                else if (LeftKey())
                {
                    ToggleMouseCursorVisibilityOnClick();
                    leftPressed = true;
                    keyPressDelayTickCount = currentTick;
                }
            }
        }
        ToggleMouseCursorVisibility();
        optionCount = 0;
        ImGui::GetIO().MouseWheel = 0;
    }

  

}