#pragma once

#include "NewWorld/Minimal.h"

#include "NewWorld/Debug/LogLevel.h"

namespace NewWorld::Debug
{
	class Logger : public Object
	{
	NW_CLASS(NewWorld::Debug, Logger)
	
		// Static
	private:
		Array<SharedPointer<Logger, true>, NW_SETTINGS_LOGGERS_COUNT> m_Loggers;

	public:


		// Members
	private:
		const String m_Name;
		const LogLevel m_ShowLevel;

	public:
		Logger(const String& name)
			: m_Name(name), m_ShowLevel(LogLevel::Debug)
		{

		}
	};
}