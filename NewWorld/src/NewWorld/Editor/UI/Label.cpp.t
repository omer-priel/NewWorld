#include "nwpch.h"
#include "Label.h"

#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	using namespace NewWorld::Editor::Components;

	// Override
	void Label::Update()
	{
		Component::Update();
		
		float marginSize = (float)LABEL_DEFUALT_MARGIN_SIZE * ((float)m_FontSize / (float)LABEL_DEFUALT_FONT_SIZE);
				
		float x = m_X;

		if (m_TextAlign == TextAlign::Left)
		{
			x += marginSize;
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
		Graphics2D::EditorDraw::DrawRectangle(m_X, m_Y, m_Width, m_Height, m_BackgroundColor);

		Graphics2D::EditorDraw::DrawString(x, m_Y + marginSize,
			m_Text, m_TextColor, m_FontSize, m_Width - marginSize * 2, m_Bold, m_Italic);
	}
}