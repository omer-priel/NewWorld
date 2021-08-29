#pragma once

#include "Dependencies.h"

#define NW_LOG(message) Debug::Log("Engine", message)
#define NW_INFO(message) Debug::Info("Engine", message)
#define NW_WARN(message) Debug::Warn("Engine", message)
#define NW_ERROR(message) Debug::Error("Engine", message)

#define LOG(message) Debug::Log("App", message)
#define INFO(message) Debug::Info("App", message)
#define WARN(message) Debug::Warn("App", message)
#define ERROR(message) Debug::Error("App", message)

namespace Debug
{
	template<typename T>
	void Log(const char* system, T obj)
	{
		std::cout << obj << "\n";
	}

	template<typename T>
	void Info(const char* system, T obj)
	{
		std::cout << "[INFO] " << system << ": " << obj << "\n";
	}

	template<typename T>
	void Warn(const char* system, T obj)
	{
		std::cout << "[WARN] " << system << ": " << obj << "\n";
	}

	template<typename T>
	void Error(const char* system, T obj)
	{
		std::cout << "[ERROR] " << system << ": " << obj << "\n";
	}
}