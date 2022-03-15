#include "nwpch.h"
#include "Label.h"

#include "NewWorld/Graphics/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	// Override
	void Label::Update()
	{
		Graphics::EditorDraw::DrawRectangle(m_X, m_Y, m_Width, m_Height, m_BackgroundColor);
		Graphics::EditorDraw::DrawString(m_X + 5, m_Y + 5, m_Text, m_TextColor, m_FontSize, m_Width - 10, m_Bold, m_Italic);

		Component::Update();
	}
}