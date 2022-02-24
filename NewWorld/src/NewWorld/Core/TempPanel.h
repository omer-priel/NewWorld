#pragma once

#include "NewWorld/Minimal.h"

#include "NewWorld/Editor/UI/Panel.h"

namespace Temp
{
	static int s_LastID = 0;

	class TempPanel : public NewWorld::Editor::UI::Panel
	{
		NW_CLASS(Temp, TempPanel)
	
	private:
		const NewWorld::uint STATES_COUNT = 10;

	private:
		NewWorld::uint m_ID = 0;
		NewWorld::uint m_State = 0;

	public:
		TempPanel(int xPos, int yPos);

		// Events
	public:
		void Create() override;

		void Update() override;

		void Click() override;
	};
}