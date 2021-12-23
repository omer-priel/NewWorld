#include "nwpch.h"
#include "Application.h"

namespace NewWorld
{
	RawPointer<Application> Application::s_Application = nullptr;

	void Application::Run()
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
}