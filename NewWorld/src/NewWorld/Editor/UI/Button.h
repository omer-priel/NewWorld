#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Component.h"
#include "NewWorld/Graphics/Color.h"
#include "NewWorld/Graphics/Colors.h"

namespace NewWorld::Editor::UI
{
	class Button : public Component
	{
	NW_CLASS(NewWorld::Editor::UI, Button)

		// Members
	private:
		String m_Text;

		uint m_FontSize;
		bool m_Bold;
		bool m_Italic;

		Graphics::Color m_BackgroundColor;
		Graphics::Color m_TextColor;
	
		bool m_Clicked = false;

	public:
		Button(float x, float y, float width, float height, const String& text,
			const Graphics::Color& backgroundColor = Graphics::Colors::EditorDarkInputBackground,
			const Graphics::Color& textColor = Graphics::Colors::EditorLightValue,
			uint fontSize = 14)
			: Component(x, y, width, height), m_Text(text), m_FontSize(fontSize),
			m_Bold(false), m_Italic(false),
			m_BackgroundColor(backgroundColor), m_TextColor(textColor)
		{

		}

		// Events
	public:
		void Update() override;

		void MouseKeyPressed(Input::Key key, float xPos, float yPos) override;
		void MouseKeyReleased(Input::Key key, float xPos, float yPos) override;


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
		void SetHeight(float height) { m_Height = height; }

		void SetText(const String& text) { m_Text = text; }

		void SetFontSize(uint fontSize) { m_FontSize = fontSize; }

		void SetBold(bool value) { m_Bold = value; }
		void SetItalic(bool value) { m_Italic = value; }

		void SetBackgroundColor(const Graphics::Color& backgroundColor) { m_BackgroundColor = backgroundColor; }
		void SetTextColor(const Graphics::Color& textColor) { m_TextColor = textColor; }
	};
}