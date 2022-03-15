#include "nwpch.h"
#include "Label.h"

#include "NewWorld/Graphics/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	// Override
	void Label::Update()
	{
		Component::Update();

		Graphics::EditorDraw::DrawRectangle(m_X, m_Y, m_Width, m_Height, m_BackgroundColor);
		
		float marginSize = (float)LABEL_DEFUALT_MARGIN_SIZE * ((float)m_FontSize / (float)LABEL_DEFUALT_FONT_SIZE);

		Graphics::EditorDraw::DrawString(m_X + marginSize, m_Y + marginSize,
			m_Text, m_TextColor, m_FontSize, m_Width - marginSize * 2, m_Bold, m_Italic);
	}
}