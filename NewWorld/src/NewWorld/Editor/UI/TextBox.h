#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Component.h"
#include "NewWorld/Graphics/Color.h"
#include "NewWorld/Graphics/Colors.h"
#include "NewWorld/Editor/UI/TextAlign.h"

namespace NewWorld::Editor::UI
{
	class TextBox : public Component
	{
	NW_CLASS(NewWorld::Editor::UI, TextBox)

		// Constants
	public:
		static const uint TEXT_BOX_DEFUALT_HEIGHT = 26;
		static const uint TEXT_BOX_DEFUALT_FONT_SIZE = 14;
		static const uint TEXT_BOX_DEFUALT_MARGIN_SIZE = 6;

		// Members
	private:
		String m_Value;
		TextAlign m_TextAlign;

		bool m_Selected;

		Graphics::Color m_BackgroundColor;
		Graphics::Color m_TextColor;

	public:
		TextBox(float x, float y, const String& defaltValue, float width, TextAlign textAlign = TextAlign::Left,
			const Graphics::Color& backgroundColor = Graphics::Colors::EditorLightInputBackground,
			const Graphics::Color& textColor = Graphics::Colors::EditorDarkValue)
			: Component(x, y, width, TEXT_BOX_DEFUALT_HEIGHT), m_Value(defaltValue), m_TextAlign(textAlign),
			m_Selected(false),
			m_BackgroundColor(backgroundColor), m_TextColor(textColor)
		{
			
		}

		// Events
	public:
		void Update() override;

		void Enter() override;
		void Leave() override;

		void KeyPressed(Input::Key key) override;
		void KeyReleased(Input::Key key) override;

		// Getters
	public:
		inline String& GetValue() { return m_Value; }

		inline TextAlign GetTextAlign() const { return m_TextAlign; }

		inline const Graphics::Color& GetBackgroundColor() const { return m_BackgroundColor; }
		inline const Graphics::Color& GetTextColor() const { return m_TextColor; }

		// Setters
	public:
		void SetX(float x) { m_X = x; }
		void SetY(float y) { m_Y = y; }

		void SetWidth(float width) { m_Width = width; }

		void SetValue(const String& value) { m_Value = value; }

		void SetText(const TextAlign& textAlign) { m_TextAlign = textAlign; }

		void SetBackgroundColor(const Graphics::Color& backgroundColor) { m_BackgroundColor = backgroundColor; }
		void SetTextColor(const Graphics::Color& textColor) { m_TextColor = textColor; }
	};
}