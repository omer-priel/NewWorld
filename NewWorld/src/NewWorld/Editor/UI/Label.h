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
		static const uint LABEL_HEIGHT = 30;
		
		// Members
	private:
		String m_Text;

		uint m_FontSize;
		bool m_Bold;
		bool m_Italic;

		Graphics::Color m_BackgroundColor;
		Graphics::Color m_TextColor;

	public:
		Label(uint x, uint y, const String& text, uint width = 0,
			const Graphics::Color& backgroundColor = Graphics::Colors::Transparency,
			const Graphics::Color& textColor = Graphics::Colors::White,
			uint fontSize = 14)
			: Component(x, y, width, LABEL_HEIGHT), m_Text(text), m_FontSize(fontSize),
			m_Bold(false), m_Italic(false),
			m_BackgroundColor(backgroundColor), m_TextColor(textColor)
		{
			
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
		void SetX(uint x) { m_X = x; }
		void SetY(uint y) { m_Y = y; }

		void SetWidth(uint width) { m_Width = width; }

		void SetText(const String& text) { m_Text = text; }

		void SetFontSize(uint fontSize) { m_FontSize = fontSize; }
		void SetBold(bool value) { m_Bold = value; }
		void SetItalic(bool value) { m_Italic = value; }

		void SetBackgroundColor(const Graphics::Color& backgroundColor) { m_BackgroundColor = backgroundColor; }
		void SetTextColor(const Graphics::Color& textColor) { m_TextColor = textColor; }
	};
}