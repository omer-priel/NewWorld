#pragma once

#include "NewWorld/Minimal.h"

int main(int argc, char** argv);

namespace NewWorld
{
	static BOOL WINAPI console_ctrl_handler(DWORD dwCtrlType)
	{
		NewWorld::Application::GetApplication().ShutDown();
		return TRUE;
	}

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
			Debug::Logger::Initialize();
			Debug::Profiler::Initialize();

			SetConsoleCtrlHandler(console_ctrl_handler, TRUE);
			
			NW_INFO(NW_LOGGER_CORE, "Engine Core Initialized.");
			
			NW_PROFILE_SCOPE("Initialize");
			this->Initialize();
		}

		void Run()
		{
			NW_PROFILE_SCOPE("Application Run");
			NW_INFO(NW_LOGGER_CORE, "The Application Start to run.");

			m_Running = true;
			// The Game Loop
			while (m_Running)
			{
				NW_PROFILE_SCOPE("Frame");
				// BeginFrame()
				
				// EndFrame()
			}

			Closed();
		}

		void Closed()
		{
			NW_INFO(NW_LOGGER_CORE, "The Application Closed");
		}

		void Cleanup()
		{
			Debug::Profiler::Finalize();
		}

		// Events
	private:


		// Action
	public:
		void ShutDown()
		{
			m_Running = false;
		}
	};

	RawPointer<Application> Application::s_Application = nullptr;
}