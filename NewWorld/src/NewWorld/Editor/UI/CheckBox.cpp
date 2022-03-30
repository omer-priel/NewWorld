#include "nwpch.h"
#include "CheckBox.h"

#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	using namespace NewWorld::Editor::Components;

	// Override
	void CheckBox::Update()
	{
		ResizableComponent::Update();

		if (m_Checked)
		{
			Graphics2D::EditorDraw::DrawRectangle(GetX(), GetY(), CHECKBOX_SIZE, CHECKBOX_SIZE,
				m_BackgroundColor + NewWorld::Graphics::ColorFunctions::FromRGBA(50, 50, 50, 0));
			
			Graphics2D::EditorDraw::DrawLine(GetX() + 8, GetY() + 2, GetX() + 3, GetY() + 7, m_ForegroundColor, 2);
			Graphics2D::EditorDraw::DrawLine(GetX() + 6, GetY() + 2, GetX() + 11, GetY() + 11, m_ForegroundColor, 2);
		}
		else
		{
			Graphics2D::EditorDraw::DrawRectangle(GetX(), GetY(), CHECKBOX_SIZE, CHECKBOX_SIZE, m_BackgroundColor);
		}
	}

	void CheckBox::Click()
	{
		Toggle();

		ResizableComponent::Click();
	}
}