#pragma once

#include "NewWorld/Minimal.h"

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

		// Getters
	public:
		inline bool IsRunning() const { return m_Running; }

		// Actions
	public:
		virtual void Init() = 0;

		void Run();
	};
}