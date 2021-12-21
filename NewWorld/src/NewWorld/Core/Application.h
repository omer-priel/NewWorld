#pragma once

#include "NewWorld/DataTypes/Object.h"

namespace NewWorld
{
	class Application : public Object
	{
	NW_CLASS(Application, NewWorld)

		// Members
	private:
		bool m_Running;

	public:
		Application()
			: m_Running(false) {}

	public:
		inline bool IsRunning() const { return m_Running; }

		// Actions
	public:
		virtual void Init() = 0;

		void Run()
		{
			// The Game Loop
			while (true)
			{
				// BeginFrame()

				// EndFrame()
			}
		}

		virtual void Test() = 0; 
	};
}