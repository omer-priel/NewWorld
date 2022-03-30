#include "nwpch.h"
#include "BordedLabel.h"

#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	// Override
	void BordedLabel::Update()
	{
		Label::Update();

		Graphics2D::EditorDraw::DrawOutlineRectangle(GetX(), GetY(), GetWidth(), GetHeight(), m_BordedColor, 2);
	}
}