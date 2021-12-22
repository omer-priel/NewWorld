#include "nwpch.h"
#include "Logger.h"

namespace NewWorld::Debug
{
	Array<SharedPointer<Logger, true>, NW_SETTINGS_LOGGERS_COUNT> Logger::s_Loggers;
	LogLevel Logger::s_ShowLevel = LogLevel::Debug;
}
