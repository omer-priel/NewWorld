#include "nwpch.h"
#include "TempPanel.h"

#include "NewWorld/Graphics/EditorDraw.h"

namespace Temp
{
	TempPanel::TempPanel(int xPos, int yPos)
		: NewWorld::Editor::UI::Panel(xPos - 20, yPos - 20, 40, 40), m_ID(s_LastID)
	{
		using namespace NewWorld;

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

		SetClickHandler([](NewWorld::Editor::Component & sender) {
			TempPanel& panel = (TempPanel&)sender;
			NW_WARN(NW_LOGGER_CORE, "{} Click", panel.m_ID);
			});

		SetMouseKeyReleasedHandler([](NewWorld::Editor::Component& sender, Input::Key key, uint xPos, uint yPos) {
			TempPanel& panel = (TempPanel&)sender;
			NW_WARN(NW_LOGGER_CORE, "{} Mouse Key Released", panel.m_ID);
			});

		SetKeyReleasedHandler([](NewWorld::Editor::Component& sender, Input::Key key) {
			TempPanel& panel = (TempPanel&)sender;
			NW_WARN(NW_LOGGER_CORE, "{} Key Released", panel.m_ID);
			});


		SetMouseHoverHandler([](NewWorld::Editor::Component& sender, uint xPos, uint yPos) {
			TempPanel& panel = (TempPanel&)sender;
			NW_WARN(NW_LOGGER_CORE, "{} Hover ({}, {})", panel.m_ID, xPos, yPos);
			});

		SetMouseScrolledHandler([](NewWorld::Editor::Component& sender, int y) {
			TempPanel& panel = (TempPanel&)sender;
			NW_WARN(NW_LOGGER_CORE, "{} Scrolled {}", panel.m_ID, y);
			});

		SetEnterHandler([](NewWorld::Editor::Component& sender) {
			TempPanel& panel = (TempPanel&)sender;
			NW_WARN(NW_LOGGER_CORE, "{} Enter", panel.m_ID);
			});

		SetLeaveHandler([](NewWorld::Editor::Component& sender) {
			TempPanel& panel = (TempPanel&)sender;
			NW_WARN(NW_LOGGER_CORE, "{} Leave", panel.m_ID);
			});

		SetCreateHandler([](NewWorld::Editor::Component& sender) {
			TempPanel& panel = (TempPanel&)sender;
			NW_WARN(NW_LOGGER_CORE, "{} Create", panel.m_ID);
			});

		SetDestroyHandler([](NewWorld::Editor::Component& sender) {
			TempPanel& panel = (TempPanel&)sender;
			NW_WARN(NW_LOGGER_CORE, "{} Destroy", panel.m_ID);
			});
	}

	// Events
	void TempPanel::Create()
	{
		using namespace NewWorld;
		NewWorld::Editor::UI::Panel::Create();

		SharedPointer<NewWorld::Editor::UI::Panel> panel1(5, 5, 10, 10, Graphics::Colors::Gold);
		panel1->SetClickHandler([](NewWorld::Editor::Component& sender) {
			NW_WARN(NW_LOGGER_CORE, "Click 1");
			});

		SharedPointer<NewWorld::Editor::UI::Panel> panel2(25, 5, 10, 10, Graphics::Colors::Gold);
		panel2->SetClickHandler([](NewWorld::Editor::Component& sender) {
			NW_WARN(NW_LOGGER_CORE, "Click 2");
			});

		SharedPointer<NewWorld::Editor::UI::Panel> panel3(5, 25, 10, 10, Graphics::Colors::Gold);
		panel3->SetClickHandler([](NewWorld::Editor::Component& sender) {
			NW_WARN(NW_LOGGER_CORE, "Click 3");
			});

		SharedPointer<NewWorld::Editor::UI::Panel> panel4(25, 25, 10, 10, Graphics::Colors::Gold);
		panel4->SetClickHandler([](NewWorld::Editor::Component& sender) {
			NW_WARN(NW_LOGGER_CORE, "Click 4");
			});

		AddComponent(panel1);
		AddComponent(panel2);
		AddComponent(panel3);
		AddComponent(panel4);
	}
	
	void TempPanel::Update()
	{
		using namespace NewWorld;
		switch (m_State)
		{
		case 0:
		{
			NewWorld::Graphics::EditorDraw::DrawString(400, 200, 400, 100,
				NewWorld::Graphics::Colors::NavyBlue, "Hello World");
		}
		break;
		case 1:
		{
			NewWorld::Graphics::EditorDraw::DrawRectangle(400, 200, 400, 100, GetBackgroundColor());
			NewWorld::Graphics::EditorDraw::DrawString(400, 200, 400, 100,
				NewWorld::Graphics::Colors::NavyBlue, "Hello World");
		}
		break;
		case 2:
		{
			NewWorld::Graphics::EditorDraw::DrawOutlineRectangle(400, 200, 400, 100, GetBackgroundColor(), 10);
			NewWorld::Graphics::EditorDraw::DrawString(400, 200, 400, 100,
				GetBackgroundColor(), "Hello World");
		}
		break;
		case 3:
		{
			NewWorld::Graphics::EditorDraw::DrawRectangle(400, 200, 400, 100, GetBackgroundColor());
		}
		break;
		case 4:
		{
			NewWorld::Graphics::EditorDraw::DrawOutlineRectangle(400, 200, 400, 100, GetBackgroundColor(), 10);
		}
		break;
		default:
		{
			NewWorld::Graphics::EditorDraw::DrawOutlineRectangle(1, 1, 100, 100, GetBackgroundColor(), 10);
		}
		break;
		}

		NewWorld::Editor::UI::Panel::Update();
	}

	void TempPanel::Click()
	{
		using namespace NewWorld;
		NewWorld::Editor::UI::Panel::Click();

		m_State = (m_State + 1) % STATES_COUNT;
		NW_WARN(NW_LOGGER_CORE, "{} State: {}", m_ID, m_State);
	}
}