#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Debug/Constants.h"
#include "NewWorld/Debug/LogLevel.h"
#include "NewWorld/Files/FileManger.h"

namespace NewWorld::Debug
{
	// This is Static class
	class Logger : public Object
	{
	NW_CLASS(NewWorld::Debug, Logger)

		// Members
	public:
		//static Files::TextFile s_LogFile;

		// Log Types
	public:
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
		static void Log(const String& log, const LogLevel level);

		static void SetColor(const LogLevel level);
	};
}