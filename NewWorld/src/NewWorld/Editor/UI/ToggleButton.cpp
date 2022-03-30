#include "nwpch.h"
#include "ToggleButton.h"

#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	using namespace NewWorld::Editor::Components;

	// Override
	void ToggleButton::Update()
	{
		ResizableComponent::Update();

		if (m_Checked)
		{
			Graphics2D::EditorDraw::DrawRectangle(GetX() + 7, GetY(), 16.0f, GetHeight(), m_BackgroundCheckedColor);
			Graphics2D::EditorDraw::DrawEllipseSlice(GetX() + 7, GetY() + 7, 7.0f, 7.0f,
				Math::PI, Math::PI, m_BackgroundCheckedColor, 12);
			Graphics2D::EditorDraw::DrawEllipseSlice(GetX() + GetWidth() - 7, GetY() + 7, 7.0f, 7.0f,
				0, Math::PI, m_BackgroundCheckedColor, 12);

			Graphics2D::EditorDraw::DrawOval(GetX() + GetWidth() - 7, GetY() + 7, 4.0f, m_ForegroundColor);
		}
		else
		{
			Graphics2D::EditorDraw::DrawRectangle(GetX() + 7, GetY(), 16.0f, GetHeight(), m_BackgroundColor);
			Graphics2D::EditorDraw::DrawEllipseSlice(GetX() + 7, GetY() + 7, 7.0f, 7.0f,
				Math::PI, Math::PI, m_BackgroundColor, 12);
			Graphics2D::EditorDraw::DrawEllipseSlice(GetX() + GetWidth() - 7, GetX() + 7, 7.0f, 7.0f,
				0, Math::PI, m_BackgroundColor, 12);

			Graphics2D::EditorDraw::DrawOval(GetX() + 7, GetY() + 7, 4.0f, m_ForegroundColor);
		}
	}

	void ToggleButton::Click()
	{
		Toggle();

		ResizableComponent::Click();
	}
}