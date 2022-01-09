#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Debug/Constants.h"
#include "NewWorld/Debug/LogLevel.h"

#include <iostream>

namespace NewWorld::Debug
{
	// Log Types
	template<typename T>
	void Debug(const char* loggerName, const LogLevel displayLevel, const T& arg)
	{
		if (displayLevel >= LogLevel::Debug)
		{
			String log = String::Format("{} [DEBUG] {}: {}\n", Time::Now(), loggerName, arg);
			std::cout.write(log.GetPointer(), log.GetLength());
		}
	}
	
	template<typename... Types>
	void Debug(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
	{
		if (displayLevel >= LogLevel::Debug)
		{
			String log = String::Format("{} [DEBUG] {}: {}\n", Time::Now(), loggerName, String::Format(format, args...));
			std::cout.write(log.GetPointer(), log.GetLength());
		}
	}

	template<typename T>
	void Info(const char* loggerName, const LogLevel displayLevel, const T& arg)
	{
		if (displayLevel >= LogLevel::Debug)
		{
			String log = String::Format("{} [INFO] {}: {}\n", Time::Now(), loggerName, arg);
			std::cout.write(log.GetPointer(), log.GetLength());
		}
	}

	template<typename... Types>
	void Info(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
	{
		if (displayLevel >= LogLevel::Info)
		{
			String log = String::Format("{} [INFO] {}: {}\n", Time::Now(), loggerName, String::Format(format, args...));
			std::cout.write(log.GetPointer(), log.GetLength());
		}
	}

	template<typename T>
	void Warn(const char* loggerName, const LogLevel displayLevel, const T& arg)
	{
		if (displayLevel >= LogLevel::Debug)
		{
			String log = String::Format("{} [WARN] {}: {}\n", Time::Now(), loggerName, arg);
			std::cout.write(log.GetPointer(), log.GetLength());
		}
	}

	template<typename... Types>
	void Warn(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
	{
		if (displayLevel >= LogLevel::Warning)
		{
			String log = String::Format("{} [WARN] {}: {}\n", Time::Now(), loggerName, String::Format(format, args...));
			std::cout.write(log.GetPointer(), log.GetLength());
		}
	}

	template<typename T>
	void Error(const char* loggerName, const LogLevel displayLevel, const T& arg)
	{
		if (displayLevel >= LogLevel::Debug)
		{
			String log = String::Format("{} [ERROR] {}: {}\n", Time::Now(), loggerName, arg);
			std::cout.write(log.GetPointer(), log.GetLength());
		}
	}

	template<typename... Types>
	void Error(const char* loggerName, const LogLevel displayLevel, const String& format, const Types&... args)
	{
		if (displayLevel >= LogLevel::Error)
		{
			String log = String::Format("{} [ERROR] {}: {}\n", Time::Now(), loggerName, String::Format(format, args...));
			std::cout.write(log.GetPointer(), log.GetLength());
		}
	}
}