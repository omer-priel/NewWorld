#pragma once

#include "NewWorld/Minimal.h"

#include "NewWorld/Editor/UI/Panel.h"
#include "NewWorld/Graphics/EditorDraw.h"

namespace Temp
{
	static int s_LastID = 0;

	using namespace NewWorld;
	class TempPanel : public Editor::UI::Panel
	{
		NW_CLASS(Temp, TempPanel)
	
	private:
		const uint STATES_COUNT = 3;

	private:
		uint m_ID = 0;
		uint m_State = 0;

	public:
		TempPanel(uint xPos, uint yPos)
			: Editor::UI::Panel(xPos - 20, yPos - 20, 40, 40), m_ID(s_LastID)
		{
			switch (m_ID % 8)
			{
			case 0:
				SetBackgroundColor(Graphics::Colors::CobaltBlue);
				break;
			case 1:
				SetBackgroundColor(Graphics::Colors::NavyBlue);
				break;
			case 2:
				SetBackgroundColor(Graphics::Colors::RoyalBlue);
				break;
			case 3:
				SetBackgroundColor(Graphics::Colors::Gold);
				break;
			case 4:
				SetBackgroundColor(Graphics::Colors::Silver);
				break;
			case 5:
				SetBackgroundColor(Graphics::Colors::Coral);
				break;
			case 6:
				SetBackgroundColor(Graphics::Colors::ForestGreen);
				break;
			case 7:
				SetBackgroundColor(Graphics::Colors::DarkRed);
				break;
			}

			s_LastID++;
			
			SetClickHandler([](Editor::Component& sender) {
				TempPanel& panel = (TempPanel&)sender;
				NW_WARN(NW_LOGGER_CORE, "{} Click", panel.m_ID);
				});

			SetMouseKeyReleasedHandler([](Editor::Component& sender, Input::Key key, uint xPos, uint yPos) {
				TempPanel& panel = (TempPanel&)sender;
				NW_WARN(NW_LOGGER_CORE, "{} Mouse Key Released", panel.m_ID);
				});

			SetKeyReleasedHandler([](Editor::Component& sender, Input::Key key) {
				TempPanel& panel = (TempPanel&)sender;
				NW_WARN(NW_LOGGER_CORE, "{} Key Released", panel.m_ID);
				});


			SetMouseHoverHandler([](Editor::Component& sender, uint xPos, uint yPos) {
				TempPanel& panel = (TempPanel&)sender;
				NW_WARN(NW_LOGGER_CORE, "{} Hover ({}, {})", panel.m_ID, xPos, yPos);
				});

			SetMouseScrolledHandler([](Editor::Component& sender, int y) {
				TempPanel& panel = (TempPanel&)sender;
				NW_WARN(NW_LOGGER_CORE, "{} Scrolled {}", panel.m_ID, y);
				});

			SetEnterHandler([](Editor::Component& sender) {
				TempPanel& panel = (TempPanel&)sender;
				NW_WARN(NW_LOGGER_CORE, "{} Enter", panel.m_ID);
				});

			SetLeaveHandler([](Editor::Component& sender) {
				TempPanel& panel = (TempPanel&)sender;
				NW_WARN(NW_LOGGER_CORE, "{} Leave", panel.m_ID);
				});

			/*SetClickHandler([](Editor::Component& sender, const Editor::Events::ClickEvent& e) {
				TempPanel& panel = (TempPanel&)sender;
				NW_WARN(NW_LOGGER_CORE, "Click Key: {}, Pos: ({}, {})", (uint)e.GetKey(), e.GetX(), e.GetY());

				Graphics::Color color = panel.GetBackgroundColor();
				color.g += 0.5f;

				SharedPointer<Editor::UI::Panel> newSubPanel(e.GetX() - 5, e.GetY() - 5, 10, 10, color);

				panel.AddComponent(newSubPanel);
			});*/

			SetCreateHandler([](Editor::Component& sender) {
				TempPanel& panel = (TempPanel&)sender;
				NW_WARN(NW_LOGGER_CORE, "{} Create", panel.m_ID);
				});

			SetDestroyHandler([](Editor::Component& sender) {
				TempPanel& panel = (TempPanel&)sender;
				NW_WARN(NW_LOGGER_CORE, "{} Destroy", panel.m_ID);
				});
		}

		// Events
	public:
		void Update() override
		{
			Editor::UI::Panel::Update();

			switch (m_State)
			{
				case 0:
				{
					Graphics::EditorDraw::DrawRectangle(GetWindow(), -50, -50, 100, 100, GetBackgroundColor());
				}
				break;
				case 1:
				{
					Graphics::EditorDraw::DrawRectangle(GetWindow(), 0, 0, 100, 100, GetBackgroundColor());
				}
				break;
				case 2:
				{
					Graphics::EditorDraw::DrawRectangle(GetWindow(), 50, 50, 100, 100, GetBackgroundColor());
				}
				break;
			}
		}

		void Click() override
		{
			Editor::UI::Panel::Click();

			m_State = (m_State + 1) % STATES_COUNT;
			NW_WARN(NW_LOGGER_CORE, "{} State: {}", m_ID, m_State);
		}
	};
}