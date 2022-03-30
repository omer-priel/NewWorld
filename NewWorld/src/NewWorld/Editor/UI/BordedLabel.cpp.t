#include "nwpch.h"
#include "BordedLabel.h"

#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	// Override
	void BordedLabel::Update()
	{
		Label::Update();

		Graphics2D::EditorDraw::DrawOutlineRectangle(m_X, m_Y, m_Width, m_Height, m_BordedColor, 2);
	}
}