#include "nwpch.h"

#define LOG(message) Debug::Log(message)
#define INFO(message) Debug::Info(message)
#define WARN(message) Debug::Warn(message)
#define ERROR(message) Debug::Error(message)

namespace Debug
{
	template<typename T>
	void Log(T obj)
	{
		std::cout << obj << "\n";
	}

	template<typename T>
	void Info(T obj)
	{
		std::cout << "[Info]: " << obj << "\n";
	}

	template<typename T>
	void Warn(T obj)
	{
		std::cout << "[Warn]: " << obj << "\n";
	}

	template<typename T>
	void Error(T obj)
	{
		std::cout << "[Error]: " << obj << "\n";
	}
}