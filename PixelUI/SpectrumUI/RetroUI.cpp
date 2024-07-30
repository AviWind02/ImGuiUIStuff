#include "../common.h"
namespace RetroBaseUI
{
	// Global Variables
	std::string subTitle = "MainMenu";
	std::string textDescription = "description Box";

	ImVec2 menuPos = { -10, 15 };
	ImVec2 menuSize = { 450.f, 775.f };

	float openstate = 475.f;
	float closedstate = 50.f;
	float pushstate = 25.f;

	int optionCount = 0;
	int currentOption = 0;
	int maxOption = 10;

	POINT lastMousePos = { 0, 0 };
	bool hasMenuOpenFinshed;

	// Font
	extern ImFont* m_font_big;



	// Colors
	ImVec4 White = ImColor(255, 255, 255, 255);
	ImVec4 spectrumpurple = ImColor(225, 96, 216);//Dark
	ImVec4 spectrumpink = ImColor(237, 155, 188);//Light
	ImVec4 spectrumcreamdark = ImColor(242, 185, 176);//Drak
	ImVec4 spectrumcreamlist = ImColor(250, 222, 158);//Light
	ImVec4 spectrumcreamdarkLowalpha = ImColor(242, 185, 176, 100);
	ImVec4 LowGrey = ImColor(25, 25, 25, 125);
	ImVec4 LowGrey150 = ImColor(25, 25, 25, 150);
	ImVec4 darkGrey = ImColor(0, 0, 0, 225);
	ImVec4 Black = ImColor(0, 0, 0, 255);
	
	// Window Sizes
	ImVec2 defaultDescriptionWindowSize = ImVec2(481, 153);
	ImVec2 defaultDescriptionWindowPos = ImVec2(1433, 856);



	void dx_init()
	{
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
		colors[ImGuiCol_Border] = spectrumpink;
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = spectrumcreamdarkLowalpha;
		colors[ImGuiCol_FrameBgHovered] = LowGrey;
		colors[ImGuiCol_FrameBgActive] = spectrumcreamlist;
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
	float fadeProgress = 0.0f;
	int fadeStage, frametimeRGB = 0;
	void UpdateFadeProgress()
	{
		if ((timeGetTime() - frametimeRGB) > 15)
		{
			fadeProgress += 0.01f; // Adjust the increment as needed

			if (fadeProgress >= 1.0f)
			{
				fadeProgress = 0.0f;
				fadeStage = (fadeStage + 1) % 5; // Move to the next stage and loop back to 0
			}

			frametimeRGB = timeGetTime();
		}
	}
	ImVec4 GetCurrentFadeColor()
	{
		UpdateFadeProgress();
		ImVec4 startColor, endColor;

		switch (fadeStage)
		{
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

	void EnlargeMenu()
	{
		int frametime = 0;

		// Delay the execution by 15 milliseconds
		if ((timeGetTime() - frametime) > 15)
		{
			// If the menu open key is clicked
			if (control::isMenuOpen)
			{
				// Gradually increase the menu width until it reaches the open state
				if (menuSize.x < openstate)
					menuSize.x += pushstate;
				else
					hasMenuOpenFinshed = true; // Set to true once the menu is fully open
			}
			else // If the open key is clicked again while the menu is open
			{
				// Gradually decrease the menu width until it reaches the closed state
				if (menuSize.x > closedstate)
					menuSize.x -= pushstate;
				hasMenuOpenFinshed = false; // Set to false so text won't show up
			}
			frametime = timeGetTime();
		}
	}

	void DrawVerticalLineFromTop(ImVec4 color, float xPos, float thickness, float menuHeight)
	{
		ImVec2 startPos = ImVec2(xPos, menuPos.y);
		ImVec2 endPos = ImVec2(xPos, menuPos.y + menuHeight);

		ImGui::GetCurrentWindow()->DrawList->AddLine(startPos, endPos, ImGui::GetColorU32(color), thickness);
	}


	void Menu()
	{
		control::ControlTick();
		EnlargeMenu();

		ImGui::SetNextWindowPos(menuPos);
		ImGui::SetNextWindowSize(menuSize);
		
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(ImColor(0, 0, 0, 175)));
		ImGui::PushStyleColor(ImGuiCol_Border, GetCurrentFadeColor());
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 2.f);
		if (ImGui::Begin("Background", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize))
		{
			if (control::isMenuOpen)
				DrawVerticalLineFromTop(GetCurrentFadeColor(), 50, 2.5f, menuSize.y);

		}
		ImGui::PopStyleVar();
		ImGui::PopStyleColor(2);
		ImGui::End();

	}



}//namespace spectrum