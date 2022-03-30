#include "nwpch.h"
#include "TextBox.h"

#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	using namespace NewWorld::Editor::Components;

	// Override
	void TextBox::Update()
	{
		ResizableComponent::Update();
		
		const float marginSize = (float)TEXT_BOX_DEFUALT_MARGIN_SIZE;

		float x = GetX();

		if (m_TextAlign == TextAlign::Left)
		{
			x += marginSize;
		}
		else
		{
			const Editor::Assets::Font& font = *(GetWindow()->GetFontManager().GetFont(0));
			Vector4 bounds = font.GetDrawBounds(m_Value, TEXT_BOX_DEFUALT_FONT_SIZE, false, false, GetWidth() - marginSize * 2);

			if (m_TextAlign == TextAlign::Center)
			{
				x += (GetWidth() - bounds.z) / 2;
			}
			else
			{
				x += GetWidth() - bounds.z - marginSize;
			}
		}

		// draw
		if (m_Selected)
		{
			Graphics2D::EditorDraw::DrawOutlineRectangle(GetX(), GetY(), GetWidth(), GetHeight(), NewWorld::Graphics::Colors::EditorBlueInputBackground, 1);
		}
		else
		{
			Graphics2D::EditorDraw::DrawOutlineRectangle(GetX(), GetY(), GetWidth(), GetHeight(), NewWorld::Graphics::Colors::EditorDarkValue, 1);
		}

		Graphics2D::EditorDraw::DrawRectangle(GetX() + 1, GetY() + 1, GetWidth() - 2, GetHeight() - 2, m_BackgroundColor);

		Graphics2D::EditorDraw::DrawString(x, GetY() + marginSize,
			m_Value, m_TextColor, TEXT_BOX_DEFUALT_FONT_SIZE, GetWidth() - marginSize * 2, false, false);
	}

	void TextBox::Enter()
	{
		Component::Enter();

		m_Selected = true;
	}

	void TextBox::Leave()
	{
		m_Selected = false;

		Component::Leave();
	}

	void TextBox::KeyPressed(Input::Key key)
	{
		if (key == Input::Key::BackSpace)
		{
			if (m_Value.GetLength() > 0)
			{
				m_Value = m_Value.Substring(0, m_Value.GetLength() - 1);
			}
		}
		else if (m_Value.GetLength() < m_MaxLength)
		{
			if (key == Input::Key::Space)
			{
				m_Value = m_Value + ' ';
			}
			else if (Input::Key::D0 <= key && key <= Input::Key::D9)
			{
				m_Value = m_Value + (char)((uint)'0' + (uint)key - (uint)Input::Key::D0);
			}
			else if (Input::Key::A <= key && key <= Input::Key::Z)
			{
				m_Value = m_Value + (char)((uint)'a' + (uint)key - (uint)Input::Key::A);
			}
		}

		Component::KeyPressed(key);
	}

	void TextBox::KeyReleased(Input::Key key)
	{
		Component::KeyReleased(key);
	}
}