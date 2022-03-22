#include "nwpch.h"
#include "ToggleButton.h"

#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	// Override
	void ToggleButton::Update()
	{
		Component::Update();

		if (m_Checked)
		{
			Graphics2D::EditorDraw::DrawRectangle(m_X + 7, m_Y, 16.0f, m_Height, m_BackgroundCheckedColor);
			Graphics2D::EditorDraw::DrawEllipseSlice(m_X + 7, m_Y + 7, 7.0f, 7.0f,
				Math::PI, Math::PI, m_BackgroundCheckedColor, 12);
			Graphics2D::EditorDraw::DrawEllipseSlice(m_X + m_Width - 7, m_Y + 7, 7.0f, 7.0f,
				0, Math::PI, m_BackgroundCheckedColor, 12);

			Graphics2D::EditorDraw::DrawOval(m_X + m_Width - 7, m_Y + 7, 4.0f, m_ForegroundColor);
		}
		else
		{
			Graphics2D::EditorDraw::DrawRectangle(m_X + 7, m_Y, 16.0f, m_Height, m_BackgroundColor);
			Graphics2D::EditorDraw::DrawEllipseSlice(m_X + 7, m_Y + 7, 7.0f, 7.0f,
				Math::PI, Math::PI, m_BackgroundColor, 12);
			Graphics2D::EditorDraw::DrawEllipseSlice(m_X + m_Width - 7, m_Y + 7, 7.0f, 7.0f,
				0, Math::PI, m_BackgroundColor, 12);

			Graphics2D::EditorDraw::DrawOval(m_X + 7, m_Y + 7, 4.0f, m_ForegroundColor);
		}
	}

	void ToggleButton::Click()
	{
		Toggle();

		Component::Click();
	}
}