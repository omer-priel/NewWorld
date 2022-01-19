#pragma once

#include "NewWorld/Minimal.h"

#include "NewWorld/Graphics/GraphicsAPI.h"

#include "NewWorld/Core/Window.h"
#include "NewWorld/Editor/EditorWindow.h"

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

	private:
		static BOOL WINAPI ConsoleCtrlHandler(DWORD type)
		{
			if (type == CTRL_CLOSE_EVENT)
			{
				NewWorld::Application::GetApplication().ShutDown();
				ExitThread(0);
			}

			return TRUE;
		}

		// Members
	private:
		bool m_Running;
		
		//Core::GameWindow m_Window; NW_CONFIG_RELEASE
		DynamicArray<SharedPointer<Editor::EditorWindow>> m_Windows;

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

			// Console Handler
			SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
			
            Graphics::GraphicsAPI::Initialize();

			NW_INFO(NW_LOGGER_CORE, "Engine Core Initialized.");

			SharedPointer<Editor::EditorWindow> window(m_Windows.size());
			m_Windows.push_back((const SharedPointer<Editor::EditorWindow>&)window);

			// Create Window
			m_Windows[0]->Create();

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

				BeginFrame();

				for (SharedPointer<Editor::EditorWindow> window : m_Windows)
				{
					window->HandleEvents();
					window->Update();
				}

				DataTypes::Thread::Sleap(100);

				EndFrame();
			}

			Closed();
		}

		void Closed()
		{
			for (SharedPointer<Editor::EditorWindow> window : m_Windows)
			{
				window->Close();
			}

			NW_INFO(NW_LOGGER_CORE, "The Application Closed");
		}

		void Cleanup()
		{
			Graphics::GraphicsAPI::Finalize();
			Debug::Profiler::Finalize();
		}

	public:
		void BeginFrame()
		{

		}

		void EndFrame()
		{

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