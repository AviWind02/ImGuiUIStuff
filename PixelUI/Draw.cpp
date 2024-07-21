#include "common.h"

namespace draw
{



	void Text(const std::string& text, ImVec4 color, ImVec2 pos, ImFont* font , bool right)
	{
		if (font == nullptr)
		{
			font = ImGui::GetDefaultFont();
		}

		ImGui::PushFont(font);
		if (right)
		{
			pos.x = ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - ImGui::CalcTextSize(text.c_str()).x
				- ImGui::GetScrollX() - 2 * ImGui::GetStyle().ItemSpacing.x;
		}

		ImGui::GetCurrentWindow()->DrawList->AddText({ pos.x + MenuPos.x, pos.y + MenuPos.y }, ImGui::GetColorU32(color), text.c_str());
		ImGui::PopFont();
	}

	std::string formatFloat(float value, int precision) 
	{
		std::ostringstream oss;
		oss.precision(precision);
		oss << std::fixed << value;
		return oss.str();
	}

	ImVec2 Add(const ImVec2& vectorA, const ImVec2& vectorB)
	{
		return ImVec2(vectorA.x + vectorB.x, vectorA.y + vectorB.y);
	}

	float GetRightTextX(float pos)
	{
		return (ImGui::GetColumnWidth() - ImGui::CalcTextSize("Right").x
			- ImGui::GetScrollX() - 2 * ImGui::GetStyle().ItemSpacing.x + pos);
	}


	void RectFilled(ImVec4 color, ImVec2 pos, ImVec2 size, bool filled)
	{
		ImVec2 actualSize = ImGui::CalcItemSize(size, 0.0f, 0.0f);
		ImVec2 topLeft = { pos.x + MenuPos.x, pos.y + MenuPos.y };
		ImVec2 bottomRight = { topLeft.x + actualSize.x, topLeft.y + actualSize.y };

		if (!filled)
		{
			ImGui::GetCurrentWindow()->DrawList->AddRect(topLeft, bottomRight, ImGui::GetColorU32(color));
		}
		else
		{
			ImGui::GetCurrentWindow()->DrawList->AddRectFilled(topLeft, bottomRight, ImGui::GetColorU32(color));
		}
	}

	void RectFilled(ImVec4 color, ImVec2 pos, ImVec2 size, bool filled, float thickness, float rounding)
	{
		ImVec2 actualSize = ImGui::CalcItemSize(size, 0.0f, 0.0f);
		ImVec2 topLeft = { pos.x + MenuPos.x, pos.y + MenuPos.y };
		ImVec2 bottomRight = { topLeft.x + actualSize.x, topLeft.y + actualSize.y };

		if (!filled)
		{
			ImGui::GetCurrentWindow()->DrawList->AddRect(topLeft, bottomRight, ImGui::GetColorU32(color), rounding, 15, thickness);
		}
		else
		{
			ImGui::GetCurrentWindow()->DrawList->AddRectFilled(topLeft, bottomRight, ImGui::GetColorU32(color));
		}
	}
	
	void RectFilled(ImVec4 color1, ImVec4 color2, ImVec4 color3, ImVec4 color4, ImVec2 pos, ImVec2 size, bool filled)
	{
		ImVec2 actualSize = ImGui::CalcItemSize(size, 0.0f, 0.0f);
		ImVec2 topLeft = { pos.x + MenuPos.x, pos.y + MenuPos.y };
		ImVec2 bottomRight = { topLeft.x + actualSize.x, topLeft.y + actualSize.y };

		if (!filled)
		{
			ImGui::GetCurrentWindow()->DrawList->AddRect(topLeft, bottomRight, ImGui::GetColorU32(color1));
		}
		else
		{
			ImGui::GetCurrentWindow()->DrawList->AddRectFilledMultiColor(topLeft, bottomRight, ImGui::GetColorU32(color1),
				ImGui::GetColorU32(color2), ImGui::GetColorU32(color3), ImGui::GetColorU32(color4));
		}
	}

	void Line(ImVec4 color, ImVec2 pos, ImVec2 rotation, float thickness)
	{
		ImVec2 size = ImGui::CalcItemSize(rotation, 0.0f, 0.0f);
		ImVec2 endPos = Add(pos, size);

		ImGui::GetCurrentWindow()->DrawList->AddLine(pos, endPos, ImGui::GetColorU32(color), thickness);
	}
}