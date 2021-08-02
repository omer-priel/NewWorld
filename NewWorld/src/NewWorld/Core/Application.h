#pragma once

namespace NewWorld
{
	class Application
	{
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
		void Run()
		{
			// The Game Loop
			while (true)
			{
				// BeginFrame()

				// EndFrame()
			}
		}
	};
}