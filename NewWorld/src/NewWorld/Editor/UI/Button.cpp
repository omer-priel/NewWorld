#include "nwpch.h"
#include "Button.h"

#include "NewWorld/Graphics/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	// Override
	void Button::Update()
	{
		Component::Update();

		Graphics::EditorDraw::DrawRectangle(m_X, m_Y, m_Width, m_Height, m_BackgroundColor);
		
		Graphics::EditorDraw::DrawString(m_X + 6, m_Y + 6,
			m_Text, m_TextColor, m_FontSize, m_Width - 12, m_Bold, m_Italic);
	}
}