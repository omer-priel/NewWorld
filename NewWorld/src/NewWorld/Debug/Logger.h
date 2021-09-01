#pragma once

#include "NewWorld/Minimal.h"

#include "Dependencies.h"

#define NW_DEBUG(...) NewWorld::Debug::Debug("Engine", ##__VA_ARGS__)
#define NW_INFO(...) NewWorld::Debug::Info("Engine", __VA_ARGS__)
#define NW_WARN(...) NewWorld::Debug::Warn("Engine", __VA_ARGS__)
#define NW_ERROR(...) NewWorld::Debug::Error("Engine", __VA_ARGS__)

#define DEBUG(...) NewWorld::Debug::Debug("App", ##__VA_ARGS__)
#define INFO(...) NewWorld::Debug::Info("App", __VA_ARGS__)
#define WARN(...) NewWorld::Debug::Warn("App", __VA_ARGS__)
#define ERROR(...) NewWorld::Debug::Error("App", __VA_ARGS__)

namespace NewWorld::Debug
{	
	template<typename... Types>
	void Debug(const char* system, Types... args)
	{
		Log("[DEBUG] ", system, ": ");
		Log(args...);
		Log("\n");
	}
	
	template<typename... Types>
	void Info(const char* system, Types... args)
	{
		Log("[INFO] ", system, ": ");
		Log(args...);
		Log("\n");
	}

	template<typename... Types>
	void Warn(const char* system, Types... args)
	{
		Log("[WARN] ", system, ": ");
		Log(args...);
		Log("\n");
	}

	template<typename... Types>
	void Error(const char* system, Types... args)
	{
		Log("[ERROR] ", system, ": ");
		Log(args...);
		Log("\n");
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
		std::cout.write(str.GetPointer(), str.GetLength());

		Log(args...);
	}

	template <typename... Types>
	void Log(const IObject& obj, Types... args)
	{
		Log(obj.ToString(), args...);
	}

	template <typename... Types>
	void Log(const Object& obj, Types... args)
	{
		Log((const IObject&)obj, args...);
	}
}