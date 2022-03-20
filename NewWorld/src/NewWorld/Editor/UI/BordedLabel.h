#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/UI/Label.h"

namespace NewWorld::Editor::UI
{
	class BordedLabel : public Label
	{
	NW_CLASS(NewWorld::Editor::UI, BordedLabel)

		// Members
	private:
		Graphics::Color m_BordedColor;

	public:
		BordedLabel(float x, float y, const String& text, float width = 0,
			const Graphics::Color& backgroundColor = Graphics::Colors::Transparency,
			const Graphics::Color& textColor = Graphics::Colors::White,
			const Graphics::Color& bordedColor = Graphics::Colors::Black,
			uint fontSize = LABEL_DEFUALT_FONT_SIZE)
			: Label(x, y, text, width, backgroundColor, textColor, fontSize), m_BordedColor(bordedColor)
		{

		}

		// Events
	public:
		void Update() override;

		// Getters
	public:
		inline const Graphics::Color& GetBordedColor() const { return m_BordedColor; }

		// Setters
	public:
		void SetBordedColor(const Graphics::Color& bordedColor) { m_BordedColor = bordedColor; }
	};
}