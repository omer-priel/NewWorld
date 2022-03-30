#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Components/ResizableComponent.h"
#include "NewWorld/Graphics/Color.h"
#include "NewWorld/Graphics/Colors.h"
#include "NewWorld/Editor/UI/TextAlign.h"

namespace NewWorld::Editor::UI
{
	class Label : public Components::ResizableComponent
	{
	NW_CLASS(NewWorld::Editor::UI, Label)

		// Constants
	public:
		static const uint LABEL_DEFUALT_HEIGHT = 26;
		static const uint LABEL_DEFUALT_FONT_SIZE = 14;
		static const uint LABEL_DEFUALT_MARGIN_SIZE = 6;

		// Members
	private:
		String m_Text;

		TextAlign m_TextAlign;

		uint m_FontSize;
		bool m_Bold;
		bool m_Italic;

		Graphics::Color m_BackgroundColor;
		Graphics::Color m_TextColor;

	public:
		Label(float x, float y, const String& text, float width = 0, TextAlign textAlign = TextAlign::Center,
			const Graphics::Color& backgroundColor = Graphics::Colors::Transparency,
			const Graphics::Color& textColor = Graphics::Colors::White,
			uint fontSize = LABEL_DEFUALT_FONT_SIZE)
			: Components::ResizableComponent(x, y, width, LABEL_DEFUALT_HEIGHT), m_Text(text), m_TextAlign(textAlign), m_FontSize(fontSize),
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

		inline TextAlign GetTextAlign() const { return m_TextAlign; }

		inline uint GetFontSize() const { return m_FontSize; }
		inline bool GetBold() const { return m_Bold; }
		inline bool GetItalic() const { return m_Italic; }

		inline const Graphics::Color& GetBackgroundColor() const { return m_BackgroundColor; }
		inline const Graphics::Color& GetTextColor() const { return m_TextColor; }

		// Setters
	public:
		void SetText(const String& text) { m_Text = text; }

		void SetText(const TextAlign& textAlign) { m_TextAlign = textAlign; }

		void SetFontSize(uint fontSize)
		{
			m_FontSize = fontSize;
			SetWidth(((float)m_FontSize / (float)LABEL_DEFUALT_FONT_SIZE) * (float)LABEL_DEFUALT_HEIGHT);
		}

		void SetBold(bool value) { m_Bold = value; }
		void SetItalic(bool value) { m_Italic = value; }

		void SetBackgroundColor(const Graphics::Color& backgroundColor) { m_BackgroundColor = backgroundColor; }
		void SetTextColor(const Graphics::Color& textColor) { m_TextColor = textColor; }
	};
}