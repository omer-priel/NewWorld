#include "nwpch.h"
#include "Label.h"

#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	using namespace NewWorld::Editor::Components;

	// Override
	void Label::Update()
	{		
		ResizableComponent::Update();

		float marginSize = (float)LABEL_DEFUALT_MARGIN_SIZE * ((float)m_FontSize / (float)LABEL_DEFUALT_FONT_SIZE);
				
		float x = GetX();

		if (m_TextAlign == TextAlign::Left)
		{
			x += marginSize;
		}
		else
		{
			const Editor::Assets::Font& font = *(GetWindow()->GetFontManager().GetFont(0));
			Vector4 bounds = font.GetDrawBounds(m_Text, m_FontSize, m_Bold, m_Italic, GetWidth() - marginSize * 2);

			if (m_TextAlign == TextAlign::Center)
			{
				x += (GetWidth() - bounds.z) / 2;
			}
			else
			{
				x += GetWidth() - bounds.z - marginSize;
			}
		}

		// draw
		Graphics2D::EditorDraw::DrawRectangle(GetX(), GetY(), GetWidth(), GetHeight(), m_BackgroundColor);

		Graphics2D::EditorDraw::DrawString(x, GetY() + marginSize,
			m_Text, m_TextColor, m_FontSize, GetWidth() - marginSize * 2, m_Bold, m_Italic);
	}
}