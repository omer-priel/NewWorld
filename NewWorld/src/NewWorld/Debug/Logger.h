#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Debug/Constants.h"
#include "NewWorld/Debug/LogLevel.h"

#include <iostream>

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
				String log = String::Format("{} [DEBUG] {}: {}\n", Time::Now(), loggerName, arg);
				std::cout.write(log.GetPointer(), log.GetLength());
			}
		}

		template<typename... Types>
		static void Debug(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
		{
			if (displayLevel >= LogLevel::Debug)
			{
				String log = String::Format("{} [DEBUG] {}: {}\n", Time::Now(), loggerName, String::Format(format, args...));
				std::cout.write(log.GetPointer(), log.GetLength());
			}
		}

		template<typename T>
		static void Info(const char* loggerName, const LogLevel displayLevel, const T& arg)
		{
			if (displayLevel >= LogLevel::Info)
			{
				String log = String::Format("{} [INFO]  {}: {}\n", Time::Now(), loggerName, arg);
				std::cout.write(log.GetPointer(), log.GetLength());
			}
		}

		template<typename... Types>
		static void Info(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
		{
			if (displayLevel >= LogLevel::Info)
			{
				String log = String::Format("{} [INFO]  {}: {}\n", Time::Now(), loggerName, String::Format(format, args...));
				std::cout.write(log.GetPointer(), log.GetLength());
			}
		}

		template<typename T>
		static void Warn(const char* loggerName, const LogLevel displayLevel, const T& arg)
		{
			if (displayLevel >= LogLevel::Warning)
			{
				String log = String::Format("{} [WARN]  {}: {}\n", Time::Now(), loggerName, arg);
				std::cout.write(log.GetPointer(), log.GetLength());
			}
		}

		template<typename... Types>
		static void Warn(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
		{
			if (displayLevel >= LogLevel::Warning)
			{
				String log = String::Format("{} [WARN]  {}: {}\n", Time::Now(), loggerName, String::Format(format, args...));
				std::cout.write(log.GetPointer(), log.GetLength());
			}
		}

		template<typename T>
		static void Error(const char* loggerName, const LogLevel displayLevel, const T& arg)
		{
			if (displayLevel >= LogLevel::Error)
			{
				String log = String::Format("{} [ERROR] {}: {}\n", Time::Now(), loggerName, arg);
				std::cout.write(log.GetPointer(), log.GetLength());
			}
		}

		template<typename... Types>
		static void Error(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
		{
			if (displayLevel >= LogLevel::Error)
			{
				String log = String::Format("{} [ERROR] {}: {}\n", Time::Now(), loggerName, String::Format(format, args...));
				std::cout.write(log.GetPointer(), log.GetLength());
			}
		}
	};
}