#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Component.h"
#include "NewWorld/Graphics/Color.h"
#include "NewWorld/Graphics/Colors.h"

namespace NewWorld::Editor::UI
{
	class Label : public Component
	{
	NW_CLASS(NewWorld::Editor::UI, Label)

		// Constants
	public:
		static const uint LABEL_DEFUALT_HEIGHT = 32;
		static const uint LABEL_DEFUALT_FONT_SIZE = 14;
		static const uint LABEL_DEFUALT_MARGIN_SIZE = 6;

		// Members
	private:
		String m_Text;

		uint m_FontSize;
		bool m_Bold;
		bool m_Italic;

		Graphics::Color m_BackgroundColor;
		Graphics::Color m_TextColor;

	public:
		Label(float x, float y, const String& text, float width = 0,
			const Graphics::Color& backgroundColor = Graphics::Colors::Transparency,
			const Graphics::Color& textColor = Graphics::Colors::White,
			uint fontSize = LABEL_DEFUALT_FONT_SIZE)
			: Component(x, y, width, LABEL_DEFUALT_HEIGHT), m_Text(text), m_FontSize(fontSize),
			m_Bold(false), m_Italic(false),
			m_BackgroundColor(backgroundColor), m_TextColor(textColor)
		{
			SetFontSize(fontSize);
		}

		// Events
	public:
		void Update() override;

		// Getters
	public:
		inline String& GetText() { return m_Text; }

		inline uint GetFontSize() const { return m_FontSize; }
		inline bool GetBold() const { return m_Bold; }
		inline bool GetItalic() const { return m_Italic; }

		inline const Graphics::Color& GetBackgroundColor() const { return m_BackgroundColor; }
		inline const Graphics::Color& GetTextColor() const { return m_TextColor; }

		// Setters
	public:
		void SetX(float x) { m_X = x; }
		void SetY(float y) { m_Y = y; }

		void SetWidth(float width) { m_Width = width; }

		void SetText(const String& text) { m_Text = text; }

		void SetFontSize(uint fontSize)
		{
			m_FontSize = fontSize;
			m_Height = ((float)m_FontSize / (float)LABEL_DEFUALT_FONT_SIZE) * (float)LABEL_DEFUALT_HEIGHT;
		}

		void SetBold(bool value) { m_Bold = value; }
		void SetItalic(bool value) { m_Italic = value; }

		void SetBackgroundColor(const Graphics::Color& backgroundColor) { m_BackgroundColor = backgroundColor; }
		void SetTextColor(const Graphics::Color& textColor) { m_TextColor = textColor; }
	};
}