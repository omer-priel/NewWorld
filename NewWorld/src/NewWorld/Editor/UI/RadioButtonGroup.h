#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Editor::UI
{
	class RadioButton;
	
	class RadioButtonGroup : public Object
	{
	NW_CLASS(NewWorld::Editor::UI, RadioButtonGroup)

		// Friends
	private:
		friend class NewWorld::Editor::UI::RadioButton;

		// Members
	private:
		DynamicArray<SharedPointer<RadioButton>> m_RadioButtons;
		//SharedPointer<RadioButton, true> m_Checked;

	public:
		RadioButtonGroup()
			//: m_Checked(nullptr)
		{

		}

		// Getters
	public:
		//inline SharedPointer<RadioButton, true> GetChecked() const { return m_Checked; }

		inline const DynamicArray<SharedPointer<RadioButton>>& GetRadioButtons() const { return m_RadioButtons; }

		// Actions
	public:
		void AddRadioButton(SharedPointer<RadioButton> radioButton);
				
		void RemoveRadioButton(uint index);
	};
}