#pragma once

#include "NewWorld/Minimal.h"

int main(int argc, char** argv);

namespace NewWorld
{
	class Application : public Object
	{
	NW_CLASS(NewWorld, Application)

		// Static
	public:
		static RawPointer<Application> s_Application;
		static inline Application& GetApplication() { return *s_Application; }

		// Members
	private:
		bool m_Running;

	public:
		Application()
			: m_Running(false)
		{
			s_Application = this;
		}

		// Friends
	private:
		friend int ::main(int argc, char** argv);

		// Getters
	public:
		inline bool IsRunning() const { return m_Running; }

		// Abstract
	protected:
		virtual void Initialize() = 0;

	private:
		void Setup()
		{
			Files::FileManger::Initialize();
			
			NW_INFO(NW_LOGGER_CORE, "Engine Core Initialized.");
			
			this->Initialize();
		}

		void Run()
		{
			NW_INFO(NW_LOGGER_CORE, "The Application Start to run.");

			m_Running = true;
			// The Game Loop
			while (m_Running)
			{
				// BeginFrame()
				ShutDown(); // TEMP
				// EndFrame()
			}

			Closed();
		}

		void Closed()
		{
			NW_INFO(NW_LOGGER_CORE, "The Application Closed");
		}

		// Action
	public:
		void ShutDown()
		{
			m_Running = false;
		}
	};

	RawPointer<Application> Application::s_Application = nullptr;
}