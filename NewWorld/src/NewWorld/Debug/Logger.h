#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Debug/Constants.h"
#include "NewWorld/Debug/LogLevel.h"

#include <iostream>

namespace NewWorld::Debug
{
	// Logs
	inline void Log() {}

	void Log(char value)
	{
		std::cout << value;
	}

	void Log(Byte value)
	{
		std::cout << value;
	}

	inline void Log(bool value)
	{
		Log((value) ? "true" : "false");
	}

	void Log(short value)
	{
		std::cout << value;
	}

	void Log(ushort value)
	{
		std::cout << value;
	}

	void Log(int value)
	{
		std::cout << value;
	}

	void Log(uint value)
	{
		std::cout << value;
	}

	void Log(Long value)
	{
		std::cout << value;
	}

	void Log(Ulong value)
	{
		std::cout << value;
	}

	void Log(float value)
	{
		std::cout << value;
	}

	// TEMP: Enums
	void Log(LogLevel value)
	{
		std::cout << (int)value;
	}

	// TEMP: Vector2 Vector3 Vector4
	void Log(Vector2 value)
	{
		std::cout << "(" << value.x << ", " << value.y << ")";
	}

	void Log(Vector3 value)
	{
		std::cout << "(" << value.x << ", " << value.y << ", " << value.z << ")";
	}

	void Log(Vector4 value)
	{
		std::cout << "(" << value.x << ", " << value.y << ", " << value.z << ", " << value.w << ")";
	}

	void Log(const char* str)
	{
		std::cout << str;
	}

	void Log(const String& str)
	{
		std::cout.write(str.GetPointer(), str.GetLength());
	}

	void Log(const IObject& obj)
	{
		Log(obj.ToString());
	}

	template <typename T>
	void Log(RawPointer<T> ptr)
	{
		if (ptr == nullptr)
		{
			Log("null");
		}
		else
		{
			Log((const T&)*ptr);
		}
	}

	template <typename T, typename... Types>
	void Log(const T& obj, const Types&... args)
	{
		if (std::is_base_of<IObject, T>::value)
		{
			Log((const IObject&)obj);
			Log(args...);
		}
		else
		{
			Log(obj);
			Log(args...);
		}
	}

	// Log Types
	template<typename... Types>
	void Debug(const char* loggerName, const LogLevel displayLevel, const Types&... args)
	{
		if (displayLevel >= LogLevel::Debug)
		{
			Log("[DEBUG] ", loggerName, ": ");
			Log(args...);
			Log("\n");
		}
	}

	template<typename... Types>
	void Info(const char* loggerName, const LogLevel displayLevel, const Types&... args)
	{
		if (displayLevel >= LogLevel::Info)
		{
			Log("[INFO] ", loggerName, ": ");
			Log(args...);
			Log("\n");
		}
	}

	template<typename... Types>
	void Warn(const char* loggerName, const LogLevel displayLevel, const Types&... args)
	{
		if (displayLevel >= LogLevel::Warning)
		{
			Log("[WARN] ", loggerName, ": ");
			Log(args...);
			Log("\n");
		}
	}

	template<typename... Types>
	void Error(const char* loggerName, const LogLevel displayLevel, const Types&... args)
	{
		if (displayLevel >= LogLevel::Error)
		{
			Log("[ERROR] ", loggerName, ": ");
			Log(args...);
			Log("\n");
		}
	}
}