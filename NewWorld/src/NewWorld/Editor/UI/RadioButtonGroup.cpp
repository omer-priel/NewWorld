#include "nwpch.h"
#include "RadioButtonGroup.h"

#include "NewWorld/Editor/UI/RadioButton.h"

namespace NewWorld::Editor::UI
{
	void RadioButtonGroup::AddRadioButton(SharedPointer<RadioButton> radioButton)
	{
		m_RadioButtons.push_back(radioButton);
		
		radioButton->m_Group = this;
		radioButton->m_Checked = false;
	}

	void RadioButtonGroup::RemoveRadioButton(uint index)
	{
		m_RadioButtons.erase(m_RadioButtons.begin() + index);

		m_RadioButtons[index]->m_Group = nullptr;
	}
}