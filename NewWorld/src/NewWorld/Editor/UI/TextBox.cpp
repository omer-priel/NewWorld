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
		Graphics::EditorDraw::DrawRectangle(m_X, m_Y, m_Width, m_Height, m_BackgroundColor);

		Graphics::EditorDraw::DrawString(x, m_Y + marginSize,
			m_Value, m_TextColor, TEXT_BOX_DEFUALT_FONT_SIZE, m_Width - marginSize * 2, false, false);
	}

	void TextBox::KeyPressed(Input::Key key)
	{
		Component::KeyReleased(key);

		NW_DEBUG(NW_LOGGER_CORE, "Key Code: {}", (uint)key);
	}

	void TextBox::KeyReleased(Input::Key key)
	{
		Component::KeyReleased(key);
	}
}