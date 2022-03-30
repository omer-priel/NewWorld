#include "nwpch.h"
#include "Button.h"

#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	using namespace NewWorld::Editor::Components;

	// Override
	void Button::Update()
	{
		ResizableComponent::Update();

		if (m_Clicked)
		{
			Graphics2D::EditorDraw::DrawRectangle(GetX(), GetY(), GetWidth(), GetHeight(), m_BackgroundColor);
			Graphics2D::EditorDraw::DrawRectangle(GetX() + 2, GetY() + 2, GetWidth() - 4, GetHeight() - 4,
				m_BackgroundColor + NewWorld::Graphics::ColorFunctions::FromRGBA(25, 25, 25, 255));
		}
		else
		{
			Graphics2D::EditorDraw::DrawRectangle(GetX(), GetY(), GetWidth(), GetHeight(), m_BackgroundColor);
		}
		
		const Assets::Font& font = *(GetWindow()->GetFontManager().GetFont(0));

		Vector4 bounds = font.GetDrawBounds(m_Text, m_FontSize, m_Bold, m_Italic, GetWidth() - 12);

		float newX = GetX() + ((GetWidth() - bounds.z + bounds.x) / 2);

		Graphics2D::EditorDraw::DrawString(newX, GetY() + 6,
			m_Text, m_TextColor, m_FontSize, GetWidth() - 12, m_Bold, m_Italic);
	}

	void Button::MouseKeyPressed(Input::Key key, float xPos, float yPos)
	{
		ResizableComponent::MouseKeyPressed(key, xPos, yPos);

		if (key == Input::Key::MouseButtonLeft)
		{
			m_Clicked = true;
		}
	}

	void Button::MouseKeyReleased(Input::Key key, float xPos, float yPos)
	{
		ResizableComponent::MouseKeyReleased(key, xPos, yPos);

		if (key == Input::Key::MouseButtonLeft)
		{
			m_Clicked = false;
		}
	}
}