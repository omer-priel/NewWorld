#include "nwpch.h"
#include "Label.h"

#include "NewWorld/Graphics/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	// Override
	void Label::Update()
	{
		Component::Update();
		
		float marginSize = (float)LABEL_DEFUALT_MARGIN_SIZE * ((float)m_FontSize / (float)LABEL_DEFUALT_FONT_SIZE);
				
		float x = m_X;

		if (m_TextAlign == TextAlign::Left)
		{
			x += marginSize;
			Graphics::EditorDraw::DrawString(m_X + marginSize, m_Y + marginSize,
				m_Text, m_TextColor, m_FontSize, m_Width - marginSize * 2, m_Bold, m_Italic);
		}
		else
		{
			const Editor::Assets::Font& font = *(GetWindow()->GetFontManager().GetFont(0));
			Vector4 bounds = font.GetDrawBounds(m_Text, m_FontSize, m_Bold, m_Italic, m_Width - marginSize * 2);

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
			m_Text, m_TextColor, m_FontSize, m_Width - marginSize * 2, m_Bold, m_Italic);
	}
}