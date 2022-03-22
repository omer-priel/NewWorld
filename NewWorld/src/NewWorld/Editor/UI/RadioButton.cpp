#include "nwpch.h"
#include "RadioButton.h"

#include "NewWorld/Editor/UI/RadioButtonGroup.h"
#include "NewWorld/Editor/Graphics/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	RadioButton::RadioButton(float x, float y,
		const Graphics::Color& backgroundColor,
		const Graphics::Color& foregroundColor,
		const Graphics::Color& foregroundCheckedColor)
		: Component(x, y, 16, 16), m_Checked(false), m_Group(nullptr),
		m_BackgroundColor(backgroundColor),
		m_ForegroundColor(foregroundColor), m_ForegroundCheckedColor(foregroundCheckedColor)
	{

	}

	// Override
	void RadioButton::Update()
	{
		Component::Update();

		if (m_Checked)
		{
			Graphics::EditorDraw::DrawOval(m_X + 8, m_Y + 8, 3, m_ForegroundCheckedColor, 32);
			Graphics::EditorDraw::DrawOutlineOval(m_X + 8, m_Y + 8, 6, m_BackgroundColor, 3, 32);
			Graphics::EditorDraw::DrawOutlineOval(m_X + 8, m_Y + 8, 8, m_ForegroundCheckedColor, 2, 32);
		}
		else
		{
			Graphics::EditorDraw::DrawOval(m_X + 8, m_Y + 8, 6, m_BackgroundColor, 32);
			Graphics::EditorDraw::DrawOutlineOval(m_X + 8, m_Y + 8, 8, m_ForegroundColor, 2, 32);
		}
	}

	void RadioButton::Click()
	{
		Component::Click();

		Toggle();
	}

	// Getters
	bool RadioButton::HasGoup()
	{
		return m_Group != nullptr;
	}

	// Actions
	void RadioButton::Toggle()
	{
		if (m_Group == nullptr)
		{
			m_Checked = !m_Checked;
		}
		else
		{
			if (!m_Checked)
			{
				m_Checked = true;
				if (m_Group->m_CheckedRadioButton != nullptr)
				{
					m_Group->m_CheckedRadioButton->m_Checked = false;
				}

				m_Group->m_CheckedRadioButton = this;
			}
		}
	}
}