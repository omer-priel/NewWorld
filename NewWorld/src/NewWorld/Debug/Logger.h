#pragma once

#include "NewWorld/Minimal.h"

#include "Dependencies.h"

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

	// Log Types
	void Log() { }

	template <typename... Types>
	void Log(char value, Types... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(Byte value, Types... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(short value, Types... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(ushort value, Types... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(int value, Types... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(uint value, Types... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(Long value, Types... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(Ulong value, Types... args)
	{
		std::cout << value;
		Log(args...);
	}

	template <typename... Types>
	void Log(float value, Types... args)
	{
		std::cout << value;
		Log(args...);
	}

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

	template <typename T, typename... Types>
	void Log(RawPointer<T> ptr, Types... args)
	{
		if (ptr == nullptr)
		{
			Log("null");
		}
		else
		{
			Log((T)*ptr);
		}

		Log(args...);
	}

	template <typename T, typename... Types>
	void Log(const T& obj, Types... args)
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

}