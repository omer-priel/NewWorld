#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Debug/Constants.h"
#include "NewWorld/Debug/LogLevel.h"

#include <iostream>

namespace NewWorld::Debug
{
	// Logs
	void Log() { }

	template <typename... Types>
	void Log(char value, const Types&... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(bool value, const Types&... args)
	{
		Log((value) ? "true" : "false", args...);
	}
	
	template <typename... Types>
	void Log(Byte value, const Types&... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(short value, const Types&... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(ushort value, const Types&... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(int value, const Types&... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(uint value, const Types&... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(Long value, const Types&... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(Ulong value, const Types&... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(float value, const Types&... args)
	{
		std::cout << value;
		Log(args...);
	}

	// TEMP: Enums
	template <typename... Types>
	void Log(LogLevel value, const Types&... args)
	{
		std::cout << (int)value;
		Log(args...);
	}

	// TEMP: Vector2 Vector3 Vector4
	template <typename... Types>
	void Log(Vector2 value, const Types&... args)
	{
		std::cout << "(" << value.x << ", " << value.y << ")";
		Log(args...);
	}

	template <typename... Types>
	void Log(Vector3 value, const Types&... args)
	{
		std::cout << "(" << value.x << ", " << value.y << ", " << value.z << ")";
		Log(args...);
	}

	template <typename... Types>
	void Log(Vector4 value, const Types&... args)
	{
		std::cout << "(" << value.x << ", " << value.y << ", " << value.z << ", " << value.w << ")";
		Log(args...);
	}

	template <typename... Types>
	void Log(const char* str, const Types&... args)
	{
		std::cout << str;
		Log(args...);
	}

	template <typename... Types>
	void Log(const String& str, const Types&... args)
	{
		std::cout.write(str.GetPointer(), str.GetLength());
		Log(args...);
	}

	template <typename... Types>
	void Log(const IObject& obj, const Types&... args)
	{
		Log(obj.ToString(), args...);
	}

	template <typename T, typename... Types>
	void Log(RawPointer<T> ptr, const Types&... args)
	{
		if (ptr == nullptr)
		{
			Log("null");
		}
		else
		{
			Log((const T&)*ptr);
		}

		Log(args...);
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
			throw "ERROR";
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