#include "nwpch.h"
#include "RadioButton.h"

//#include "NewWorld/Editor/UI/RadioButtonGroup.h"
#include "NewWorld/Graphics/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	RadioButton::RadioButton(uint x, uint y, //SharedPointer<RadioButtonGroup> group,
		const Graphics::Color& backgroundColor,
		const Graphics::Color& foregroundColor,
		const Graphics::Color& foregroundCheckedColor)
		: Component(x, y, 14, 14), m_Checked(false),// m_Group(group),
		m_BackgroundColor(backgroundColor),
		m_ForegroundColor(foregroundColor), m_ForegroundCheckedColor(foregroundCheckedColor)
	{
		//m_Group->AddRadioButton(this);
	}

	// Override
	void RadioButton::Update()
	{
		Component::Update();

		if (m_Checked)
		{
			Graphics::EditorDraw::DrawOval(m_X + 7, m_Y + 7, 4, m_ForegroundColor);
		}
		else
		{
			Graphics::EditorDraw::DrawEllipseSlice(m_X + 7, m_Y + 7, 7, 7,
				Math::PI, Math::PI, m_BackgroundColor, 12);
			Graphics::EditorDraw::DrawEllipseSlice(m_X + 7, m_Y + 7, 7, 7,
				0, Math::PI, m_BackgroundColor, 12);

			Graphics::EditorDraw::DrawOval(m_X + 7, m_Y + 7, 4, m_ForegroundColor);
		}
	}

	void RadioButton::Click()
	{
		Component::Click();

		Checked();
	}

	void RadioButton::Checked()
	{
		if (!m_Checked)
		{
			m_Checked = true;
		}
	}
}