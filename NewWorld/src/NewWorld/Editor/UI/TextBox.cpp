#include "nwpch.h"
#include "TextBox.h"

#include "NewWorld/Graphics/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	// Override
	void TextBox::Update()
	{
		Component::Update();
		
		const float marginSize = (float)TEXT_BOX_DEFUALT_MARGIN_SIZE;

		float x = m_X;

		if (m_TextAlign == TextAlign::Left)
		{
			x += marginSize;
		}
		else
		{
			const Editor::Assets::Font& font = *(GetWindow()->GetFontManager().GetFont(0));
			Vector4 bounds = font.GetDrawBounds(m_Value, TEXT_BOX_DEFUALT_FONT_SIZE, false, false, m_Width - marginSize * 2);

			if (m_TextAlign == TextAlign::Center)
			{
				x += (m_Width - bounds.z) / 2;
			}
			else
			{
				x += m_Width - bounds.z - marginSize;
			}
		}

		// draw
		if (m_Selected)
		{
			Graphics::EditorDraw::DrawOutlineRectangle(m_X, m_Y, m_Width, m_Height, Graphics::Colors::EditorBlueInputBackground, 1);
		}
		else
		{
			Graphics::EditorDraw::DrawOutlineRectangle(m_X, m_Y, m_Width, m_Height, Graphics::Colors::EditorDarkValue, 1);
		}

		Graphics::EditorDraw::DrawRectangle(m_X+1, m_Y+1, m_Width-2, m_Height-2, m_BackgroundColor);

		Graphics::EditorDraw::DrawString(x, m_Y + marginSize,
			m_Value, m_TextColor, TEXT_BOX_DEFUALT_FONT_SIZE, m_Width - marginSize * 2, false, false);
	}

	void TextBox::Enter()
	{
		Component::Enter();

		m_Selected = true;
	}

	void TextBox::Leave()
	{
		m_Selected = false;

		Component::Leave();
	}

	void TextBox::KeyPressed(Input::Key key)
	{
		Component::KeyReleased(key);

		NW_DEBUG(NW_LOGGER_CORE, "Key Code: {}", (uint)key);

		if (m_Value.GetLength() < m_MaxLength)
		{
			if (key == Input::Key::Space)
			{
				m_Value = m_Value + ' ';
			}
			else if (Input::Key::D0 <= key && key <= Input::Key::D9)
			{
				m_Value = m_Value + (char)((uint)'0' + (uint)key - (uint)Input::Key::D0);
			}
			else if (Input::Key::A <= key && key <= Input::Key::Z)
			{
				m_Value = m_Value + (char)((uint)'a' + (uint)key - (uint)Input::Key::A);
			}
		}
	}

	void TextBox::KeyReleased(Input::Key key)
	{
		Component::KeyReleased(key);
	}
}