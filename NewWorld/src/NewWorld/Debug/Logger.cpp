#include "nwpch.h"
#include "Logger.h"

#include <iostream>

#if NW_PLATFORM_WINDOWS
#include <windows.h>
#endif

namespace NewWorld::Debug
{
	// Members
	Files::TextFile Logger::s_LogFile;

	// Actions
	void Logger::Initialize()
	{
		s_LogFile.Open(Files::FileManger::GetLogsDirectory(Time::Now().Format("{}_{}_{}.log")), true);
	}

	// Log
	void Logger::Log(const String& log, const LogLevel level)
	{		
		// Console
		Logger::SetColor(level);
		std::cout.write(log.GetPointer(), log.GetLength());
		
		// Log File
		s_LogFile.Write(log);
	}


	void Logger::SetColor(const LogLevel level)
	{
#if NW_PLATFORM_WINDOWS
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		switch (level)
		{
		case LogLevel::Critical:
			SetConsoleTextAttribute(hConsole, 0xF4); // Dark Red on White
			break;
		case LogLevel::Error:
			SetConsoleTextAttribute(hConsole, 0x04); // Dark Red
			break;
		case LogLevel::Warning:
			SetConsoleTextAttribute(hConsole, 0x06); // Orange
			break;
		case LogLevel::Info:
			SetConsoleTextAttribute(hConsole, 0x02); // Dark Green
			break;
		case LogLevel::Debug:
			SetConsoleTextAttribute(hConsole, 0x0F); // White
			break;
		}
#elif NW_PLATFORM_LINUX
#error TODO
#endif
	}
}