#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Component.h"

namespace NewWorld::Editor::UI
{
	class RadioButton;
	
	class RadioButtonGroup : public Component
	{
	NW_CLASS(NewWorld::Editor::UI, RadioButtonGroup)

		// Friends
	private:
		friend class NewWorld::Editor::UI::RadioButton;

		// Members
	private:
		DynamicArray<SharedPointer<RadioButton>> m_RadioButtons;
		RawPointer<RadioButton> m_CheckedRadioButton;

	public:
		RadioButtonGroup()
			: Component(0, 0, 0, 0), m_CheckedRadioButton(nullptr)
		{

		}

		// Getters
	public:
		inline RawPointer<RadioButton> GetCheckedRadioButton() const { return m_CheckedRadioButton; }

		inline const DynamicArray<SharedPointer<RadioButton>>& GetRadioButtons() const { return m_RadioButtons; }

		// Actions
	public:
		void AddRadioButton(SharedPointer<RadioButton> radioButton);
				
		void RemoveRadioButton(uint index);
	};
}