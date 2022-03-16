#include "nwpch.h"
#include "ToggleButton.h"

#include "NewWorld/Graphics/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	// Override
	void ToggleButton::Update()
	{
		Component::Update();

		if (m_Checked)
		{
			Graphics::EditorDraw::DrawRectangle(m_X + 7, m_Y, 16, m_Height, m_BackgroundCheckedColor);
			Graphics::EditorDraw::DrawEllipseSlice(m_X + 7, m_Y + 7, 7, 7, 
				Math::PI, Math::PI, m_BackgroundCheckedColor, 12);
			Graphics::EditorDraw::DrawEllipseSlice(m_X + m_Width - 7, m_Y + 7, 7, 7, 
				0, Math::PI, m_BackgroundCheckedColor, 12);

			Graphics::EditorDraw::DrawOval(m_X + m_Width - 7, m_Y + 7, 4, m_ForegroundColor);
		}
		else
		{
			Graphics::EditorDraw::DrawRectangle(m_X + 7, m_Y, 16, m_Height, m_BackgroundColor);
			Graphics::EditorDraw::DrawEllipseSlice(m_X + 7, m_Y + 7, 7, 7,
				Math::PI, Math::PI, m_BackgroundColor, 12);
			Graphics::EditorDraw::DrawEllipseSlice(m_X + m_Width - 7, m_Y + 7, 7, 7,
				0, Math::PI, m_BackgroundColor, 12);

			Graphics::EditorDraw::DrawOval(m_X + 7, m_Y + 7, 4, m_ForegroundColor);
		}
	}

	void ToggleButton::Click()
	{
		Toggle();

		Component::Click();
	}
}