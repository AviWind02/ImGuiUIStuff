#pragma once
#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <sstream>


#include <D3D11.h>
#include "d3d11.h"
#pragma comment(lib, "d3d11.lib")

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_internal.h"

#include "notify/notify.h"
#include "rubik.h"


#include <ctime>
#include <timeapi.h>
#include <time.h>



# pragma comment(lib, "secur32.lib")
# pragma comment(lib, "winmm.lib")
# pragma comment(lib, "dmoguids.lib")
# pragma comment(lib, "wmcodecdspuuid.lib")
# pragma comment(lib, "msdmo.lib")
# pragma comment(lib, "Strmiids.lib")




extern ImFont* m_font, * m_font_big, * m_font_title, * m_font_icon, *m_font_small;


namespace RetroBaseUI
{
    void Menu();
    void dx_init();
}
namespace HawkBaseUI {
    void RenderMenu();
}
namespace NoNameUI {
    void RenderMenu();
}
namespace SideUI {
    void RenderMenu();
}
namespace BsaicUI {
    void RenderMenu();
}




//BoxUI
extern ImVec2 MenuPos;
extern int optionCount;
extern int currentOption;
extern int maxOption;
extern float optionYOffset;
extern float optionYStart;
extern float headerOffsetX;
extern float footerYPosition;
extern ImVec2 optionSize;
void RenderMenu();



#ifndef CONTROL_H
#define CONTROL_H
namespace control
{
    // Key press delay and other variables
    extern int keyPressDelay;
    extern int maxOptionForTop;
    extern uint64_t keyPressDelayTickCount;

    // Menu state variables
    extern bool leftPressed;
    extern bool rightPressed;
    extern bool selectPressed;
    extern bool isMenuOpen;
    extern bool isMouseEnabled;
    extern bool cursorVisible;

    bool IsKeyPressed(int virtualKey);

    bool Forward();
    bool ShiftL();
    bool Backward();
    bool RightSideward();
    bool LeftSideward();
    bool OpenKey();
    bool MouseKey();
    bool FavKey();
    bool ScrollTopMenu();
    bool UpKey();
    bool ScrollUp();
    bool ScrollDown();
    bool DownKey();
    bool RightKey();
    bool LeftKey();
    bool SelectKey();
    bool BackKey();

    bool MouseClick(const std::string& text, ImVec2 pos, ImVec2 size, bool* out_hovered, bool* out_held);
    bool MouseClickOption(const std::string& text, bool* out_hovered, bool* out_held);

    void ToggleMouseCursorVisibility();
    void ControlTick();
}

#endif // CONTROL_H

#ifndef DRAW_H
#define DRAW_H
namespace draw
{
    ImVec2 Add(const ImVec2& vectorA, const ImVec2& vectorB);
    float GetRightTextX(float pos);
    std::string FormatFloat(float value, int precision);
    void RectFilled(ImVec4 color, ImVec2 pos, ImVec2 size, bool filled = true);
    void RectFilled(ImVec4 color, ImVec2 pos, ImVec2 size, ImDrawCornerFlags rounding_corners, float rounding);
        void RectFilled(ImVec4 color1, ImVec4 color2, ImVec4 color3, ImVec4 color4, ImVec2 pos, ImVec2 size, bool filled);
    void Line(ImVec4 color, ImVec2 pos, ImVec2 rotation, float thickness);
    void Text(const std::string& text, ImVec4 color, ImVec2 pos, ImFont* font = nullptr, bool right = false, bool center = false);
}

#endif // DRAW_H


