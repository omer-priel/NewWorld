#pragma once

#include "NewWorld/DataTypes/Object.h"

namespace NewWorld
{
	class Application : public Object
	{
	NW_CLASS(NewWorld, Application)

		// Members
	private:
		bool m_Running;

	public:
		Application()
			: m_Running(false) {}

		// Getters
	public:
		inline bool IsRunning() const { return m_Running; }

		// Actions
	public:
		virtual void Init() = 0;

		void Run()
		{
			m_Running = true;
			// The Game Loop
			while (m_Running)
			{
				// BeginFrame()
				m_Running = false;
				// EndFrame()
			}
		}
	};
}