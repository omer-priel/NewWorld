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
		
		const Editor::Assets::Font& font = *(GetWindow()->GetFontManager().GetFont(0));

		Vector4 bounds = font.GetDrawBounds(m_Text, m_FontSize, m_Bold, m_Italic, m_Width);

		float newX = m_X + (((float)m_Width - bounds.z + bounds.x) / 2);

		Graphics::EditorDraw::DrawString(newX, m_Y + 6,
			m_Text, m_TextColor, m_FontSize, m_Width, m_Bold, m_Italic);
	}
}