#include "nwpch.h"
#include "CheckBox.h"

#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	using namespace NewWorld::Editor::Components;

	// Override
	void CheckBox::Update()
	{
		Component::Update();

		if (m_Checked)
		{
			Graphics2D::EditorDraw::DrawRectangle(m_X, m_Y, m_Width, m_Height,
				m_BackgroundColor + NewWorld::Graphics::ColorFunctions::FromRGBA(50, 50, 50, 0));
			
			Graphics2D::EditorDraw::DrawLine(m_X + 8, m_Y + 2, m_X + 3, m_Y + 7, m_ForegroundColor, 2);
			Graphics2D::EditorDraw::DrawLine(m_X + 6, m_Y + 2, m_X + 11, m_Y + 11, m_ForegroundColor, 2);
		}
		else
		{
			Graphics2D::EditorDraw::DrawRectangle(m_X, m_Y, m_Width, m_Height, m_BackgroundColor);
		}
	}

	void CheckBox::Click()
	{
		Toggle();

		Component::Click();
	}
}