#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Component.h"
#include "NewWorld/Graphics/Color.h"
#include "NewWorld/Graphics/Colors.h"

namespace NewWorld::Editor::UI
{
	class RadioButtonGroup;

	class RadioButton : public Component
	{
	NW_CLASS(NewWorld::Editor::UI, RadioButton)

		// Friends
	private:
		friend class NewWorld::Editor::UI::RadioButtonGroup;

		// Members
	private:
		bool m_Checked;
		SharedPointer<RadioButtonGroup, true> m_Group; // Controlled by RadioButtonGroup

		Graphics::Color m_BackgroundColor;
		Graphics::Color m_ForegroundColor;
		Graphics::Color m_ForegroundCheckedColor;

	public:
		RadioButton(uint x, uint y,
			const Graphics::Color& backgroundColor = Graphics::Colors::EditorLightInputBackground,
			const Graphics::Color& foregroundColor = Graphics::Colors::EditorDarkValue,
			const Graphics::Color& foregroundCheckedColor = Graphics::Colors::EditorBlueValue);

		// Events
	public:
		void Update() override;

		void Click() override;

		// Getters
	public:
		inline bool IsChecked() const  { return m_Checked; }
		bool HasGoup();

		inline const Graphics::Color& GetBackgroundColor() const { return m_BackgroundColor; }
		inline const Graphics::Color& GetForegroundColor() const { return m_ForegroundColor; }
		inline const Graphics::Color& GetForegroundCheckedColor() const { return m_ForegroundCheckedColor; }

		// Setters
	public:
		void SetX(uint x) { m_X = x; }
		void SetY(uint y) { m_Y = y; }

	public:
		void SetBackgroundColor(const Graphics::Color& color) { m_BackgroundColor = color; }
		void SetForegroundColor(const Graphics::Color& color) { m_ForegroundColor = color; }
		void SetForegroundCheckedColor(const Graphics::Color& color) { m_ForegroundCheckedColor = color; }

		// Actions
	public:
		void Toggle();
	};
}