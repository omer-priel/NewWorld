#include "nwpch.h"
#include "Button.h"

#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	// Override
	void Button::Update()
	{
		Component::Update();

		if (m_Clicked)
		{
			Graphics2D::EditorDraw::DrawRectangle(m_X, m_Y, m_Width, m_Height, m_BackgroundColor);
			Graphics2D::EditorDraw::DrawRectangle(m_X+2, m_Y+2, m_Width-4, m_Height-4,
				m_BackgroundColor + NewWorld::Graphics::ColorFunctions::FromRGBA(25, 25, 25, 255));
		}
		else
		{
			Graphics2D::EditorDraw::DrawRectangle(m_X, m_Y, m_Width, m_Height, m_BackgroundColor);
		}
		
		const Assets::Font& font = *(GetWindow()->GetFontManager().GetFont(0));

		Vector4 bounds = font.GetDrawBounds(m_Text, m_FontSize, m_Bold, m_Italic, m_Width - 12);

		float newX = m_X + ((m_Width - bounds.z + bounds.x) / 2);

		Graphics2D::EditorDraw::DrawString(newX, m_Y + 6,
			m_Text, m_TextColor, m_FontSize, m_Width - 12, m_Bold, m_Italic);
	}

	void Button::MouseKeyPressed(Input::Key key, float xPos, float yPos)
	{
		Component::MouseKeyPressed(key, xPos, yPos);

		if (key == Input::Key::MouseButtonLeft)
		{
			m_Clicked = true;
		}
	}

	void Button::MouseKeyReleased(Input::Key key, float xPos, float yPos)
	{
		Component::MouseKeyReleased(key, xPos, yPos);

		if (key == Input::Key::MouseButtonLeft)
		{
			m_Clicked = false;
		}
	}
}