#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Component.h"
#include "NewWorld/Graphics/Color.h"
#include "NewWorld/Graphics/Colors.h"

namespace NewWorld::Editor::UI
{
	class CheckBox : public Component
	{
	NW_CLASS(NewWorld::Editor::UI, CheckBox)

		// Constants
	public:
		static const uint CHECKBOX_SIZE = 14;

		// Members
	private:
		bool m_Checked;

		Graphics::Color m_BackgroundColor;
		Graphics::Color m_ForegroundColor;

	public:
		CheckBox(uint x, uint y, bool checked = false,
			const Graphics::Color& backgroundColor = Graphics::Colors::EditorDarkInputBackground,
			const Graphics::Color& foregroundColor = Graphics::Colors::EditorDarkValue)
			: Component(x, y, CHECKBOX_SIZE, CHECKBOX_SIZE), m_Checked(checked),
			m_BackgroundColor(backgroundColor), m_ForegroundColor(foregroundColor)
		{

		}

		// Events
	public:
		void Update() override;

		void Click() override;

		// Getters
	public:
		inline bool IsChecked() const  { return m_Checked; }

		inline const Graphics::Color& GetBackgroundColor() const { return m_BackgroundColor; }
		inline const Graphics::Color& GetForegroundColor() const { return m_ForegroundColor; }

		// Setters
	public:
		void SetX(uint x) { m_X = x; }
		void SetY(uint y) { m_Y = y; }

		void SetChecked(bool checked) { m_Checked = checked; }

		void SetBackgroundColor(const Graphics::Color& backgroundColor) { m_BackgroundColor = backgroundColor; }
		void SetForegroundColor(const Graphics::Color& foregroundColor) { m_ForegroundColor = foregroundColor; }

		// Actions
	public:
		void Toggle() { m_Checked = !m_Checked; }
	};
}