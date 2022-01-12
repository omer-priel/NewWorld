#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Debug/Constants.h"
#include "NewWorld/Debug/LogLevel.h"

#include <iostream>

#if NW_PLATFORM_WINDOWS
#include <windows.h>
#endif

namespace NewWorld::Debug
{
	// This is Static class
	class Logger : public Object
	{
		NW_CLASS(NewWorld::Debug, Logger)

	public:
		// Log Types
		template<typename T>
		static void Debug(const char* loggerName, const LogLevel displayLevel, const T& arg)
		{
			if (displayLevel >= LogLevel::Debug)
			{
				String log = String::Format("{} [DEBUG] {}: {}\n", Time::Now().ToString(true), loggerName, arg);
				Logger::Log(log, LogLevel::Debug);
			}
		}

		template<typename... Types>
		static void Debug(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
		{
			if (displayLevel >= LogLevel::Debug)
			{
				String log = String::Format("{} [DEBUG] {}: {}\n", Time::Now().ToString(true), loggerName, String::Format(format, args...));
				Logger::Log(log, LogLevel::Debug);
			}
		}

		template<typename T>
		static void Info(const char* loggerName, const LogLevel displayLevel, const T& arg)
		{
			if (displayLevel >= LogLevel::Info)
			{
				String log = String::Format("{} [INFO]  {}: {}\n", Time::Now().ToString(true), loggerName, arg);
				Logger::Log(log, LogLevel::Info);
			}
		}

		template<typename... Types>
		static void Info(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
		{
			if (displayLevel >= LogLevel::Info)
			{
				String log = String::Format("{} [INFO]  {}: {}\n", Time::Now().ToString(true), loggerName, String::Format(format, args...));
				Logger::Log(log, LogLevel::Info);
			}
		}

		template<typename T>
		static void Warn(const char* loggerName, const LogLevel displayLevel, const T& arg)
		{
			if (displayLevel >= LogLevel::Warning)
			{
				String log = String::Format("{} [WARN]  {}: {}\n", Time::Now().ToString(true), loggerName, arg);
				Logger::Log(log, LogLevel::Warning);
			}
		}

		template<typename... Types>
		static void Warn(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
		{
			if (displayLevel >= LogLevel::Warning)
			{
				String log = String::Format("{} [WARN]  {}: {}\n", Time::Now().ToString(true), loggerName, String::Format(format, args...));
				Logger::Log(log, LogLevel::Warning);
			}
		}

		template<typename T>
		static void Error(const char* loggerName, const LogLevel displayLevel, const T& arg)
		{
			if (displayLevel >= LogLevel::Error)
			{
				String log = String::Format("{} [ERROR] {}: {}\n", Time::Now().ToString(true), loggerName, arg);
				Logger::Log(log, LogLevel::Error);
			}
		}

		template<typename... Types>
		static void Error(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
		{
			if (displayLevel >= LogLevel::Error)
			{
				String log = String::Format("{} [ERROR] {}: {}\n", Time::Now().ToString(true), loggerName, String::Format(format, args...));
				Logger::Log(log, LogLevel::Error);
			}
		}

		template<typename T>
		static void Critical(const char* loggerName, const LogLevel displayLevel, const T& arg)
		{
			if (displayLevel >= LogLevel::Critical)
			{
				String log = String::Format("{} [CRITICAL] {}: {}\n", Time::Now().ToString(true), loggerName, arg);
				Logger::Log(log, LogLevel::Critical);
			}
		}

		template<typename... Types>
		static void Critical(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
		{
			if (displayLevel >= LogLevel::Critical)
			{
				String log = String::Format("{} [CRITICAL] {}: {}\n", Time::Now().ToString(true), loggerName, String::Format(format, args...));
				Logger::Log(log, LogLevel::Critical);
			}
		}

	private:
		static inline void Log(const String& log, const LogLevel level)
		{
			Logger::SetColor(level);
			std::cout.write(log.GetPointer(), log.GetLength());
			// Save Log
		}

		static inline void SetColor(const LogLevel level)
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
	};
}