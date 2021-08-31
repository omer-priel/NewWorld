#pragma once

#include "Dependencies.h"

#define NW_DEBUG(message) NewWorld::Debug::Debug("Engine", message)
#define NW_INFO(message) NewWorld::Debug::Info("Engine", message)
#define NW_WARN(message) NewWorld::Debug::Warn("Engine", message)
#define NW_ERROR(message) NewWorld::Debug::Error("Engine", message)

#define DEBUG(message) NewWorld::Debug::Debug("App", message)
#define INFO(message) NewWorld::Debug::Info("App", message)
#define WARN(message) NewWorld::Debug::Warn("App", message)
#define ERROR(message) NewWorld::Debug::Error("App", message)

namespace NewWorld::Debug
{
	template<typename T>
	void Debug(const char* system, T obj)
	{
		Log("[DEBUG] ", system, ": ", obj, "\n");
	}
	
	template<typename T>
	void Info(const char* system, T obj)
	{
		//Log("[INFO] ", system, ": ", obj, "\n");
	}

	template<typename T>
	void Warn(const char* system, T obj)
	{
		//Log("[WARN] ", system, ": ", obj, "\n");
	}

	template<typename T>
	void Error(const char* system, T obj)
	{
		//Log("[ERROR] ", system, ": ", obj, "\n")
	}

	// Log Variadic types
	template <typename T, typename... Types>
	void Log(T var1, Types... args)
	{
		Log(args...);
	}

	void Log() { }

	// Log Types
	template <typename... Types>
	void Log(const char* str, Types... args)
	{
		std::cout << str;

		Log(args...);
	}

	template <typename... Types>
	void Log(const String& str, Types... args)
	{
		std::cout << str.m_Value;

		Log(args...);
	}

	template <typename... Types>
	void Log(const IObject& obj, Types... args)
	{
		std::cout << obj.ToString();

		Log(args...);
	}

	template <typename... Types>
	void Log(const Object& obj, Types... args)
	{
		std::cout << obj.ToString();

		Log(args...);
	}
}