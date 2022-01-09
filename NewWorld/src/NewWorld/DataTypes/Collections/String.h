#pragma once

#include "NewWorld/DataTypes/IObject.h"
#include "NewWorld/DataTypes/Type.h"
#include "NewWorld/DataTypes/Collections/Array.h"

#include <string>
#include <format>

// Temp
#include "NewWorld/Debug/LogLevel.h"

#include "NewWorld/Math/Vector2.h"
#include "NewWorld/Math/Vector3.h"
#include "NewWorld/Math/Vector4.h"
#include "NewWorld/Math/Matrix2.h"
#include "NewWorld/Math/Matrix3.h"
#include "NewWorld/Math/Matrix4.h"

#include <iostream>

namespace NewWorld
{
	using Vector2 = Math::Vector2;
	using Vector3 = Math::Vector3;
	using Vector4 = Math::Vector4;

	using Matrix2 = Math::Matrix2;
	using Matrix3 = Math::Matrix3;
	using Matrix4 = Math::Matrix4;
}

namespace NewWorld::DataTypes::Collections
{
	class String : public IObject
	{
	NW_CLASS(NewWorld::DataTypes::Collections, String)

		// Static Convert To String
	public:
		template <typename T>
		static String ConverToString(T value)
		{
			std::cout << typeid(T).name();
			throw "Error";
		}

		template <typename T>
		static String ConverToString(T* ptr)
		{
			if (ptr == nullptr)
			{
				return String("null");
			}
			else
			{
				return ConverToString(*ptr);
			}
		}
		
		template <>
		static String ConverToString(char value)
		{
			return String(std::to_string(value).c_str());
		}

		template <>
		static String ConverToString(Byte value)
		{
			return String(std::to_string(value).c_str());
		}
		
		template <>
		static String ConverToString(bool value)
		{
			return String((value) ? "true" : "false");
		}
		
		template <>
		static String ConverToString(short value)
		{
			return String(std::to_string(value).c_str());
		}

		template <>
		static String ConverToString(ushort value)
		{
			return String(std::to_string(value).c_str());
		}
		
		template <>
		static String ConverToString(int value)
		{
			return String(std::to_string(value).c_str());
		}

		template <>
		static String ConverToString(uint value)
		{
			return String(std::to_string(value).c_str());
		}
		
		template <>
		static String ConverToString(Long value)
		{
			return String(std::to_string(value).c_str());
		}
		
		template <>
		static String ConverToString(Ulong value)
		{
			return String(std::to_string(value).c_str());
		}
		
		template <>
		static String ConverToString(float value)
		{
			return String(std::to_string(value).c_str());
		}
		
		// TEMP: Enums
		template <>
		static String ConverToString(const Debug::LogLevel& value)
		{
			return ConverToString((Byte)value);
		}
		
		// TEMP: Vector2 Vector3 Vector4
		template <>
		static String ConverToString(Vector2 value)
		{
			return String("(0,0)");
			//return String::Format("({}, {})", value.x, value.y);
		}
		
		template <>
		static String ConverToString(Vector3 value)
		{
			return String("(0,0,0)");
			//return String::Format("({}, {}, {})", value.x, value.y, value.z);
		}

		template <>
		static String ConverToString(Vector4 value)
		{
			return String("(0,0,0,0)");
			//return String::Format("({}, {}, {}, {})", value.x, value.y, value.z, value.w);
		}
		
		template <>
		static String ConverToString(const String& str)
		{
			return str;
		}

		template <>
		static String ConverToString(const char* str)
		{
			return String(str);
		}
		
		template <>
		static String ConverToString(const IObject& obj)
		{
			return obj.ToString();
		}

		template<typename... Types>
		static Array<String, (SizeT)sizeof...(Types)> ConverToStringArray(const Types&... args)
		{
			const SizeT LENGTH = (SizeT)sizeof...(Types);
			Array<String, LENGTH> arr;

			ConverToStringLoader<LENGTH, Types...>(arr, args...);

			return arr;
		}

		template<const SizeT LENGTH>
		static void ConverToStringLoader(Array<String, LENGTH>& arr)
		{

		}
		
		template<const SizeT LENGTH, typename T, typename... Types>
		static void ConverToStringLoader(Array<String, LENGTH>& arr, const T& arg, const Types&... args)
		{
			SizeT index = LENGTH - ((SizeT)sizeof...(Types)) - 1;
			if (std::is_base_of<IObject, T>::value)
			{
				arr[index] = ((const IObject&)arg).ToString();
			}
			else
			{
				arr[index] = String::ConverToString(arg);
			}

			ConverToStringLoader<LENGTH, Types...>(arr, args...);
		}
		
		// Static
	public:
		template<typename... Types>
		static String Format(String format, const Types&... args)
		{
			Array<String, (SizeT)sizeof...(Types)> values = ConverToStringArray(args...);
			std::ostringstream stream;
			uint index = 0;
			uint valuesIndex = 0;
			uint nextArg = 0;
			while (index < format.GetLength() && nextArg != -1) {
				nextArg = format.Find("{}", index);
				if (nextArg != -1)
				{
					stream.write(&(format[index]), nextArg - index);
					if (valuesIndex < values.size())
					{
						stream.write(values[valuesIndex].GetPointer(), values[valuesIndex].GetLength());
						valuesIndex++;
					}
					index = nextArg + 2;
				}
			}
			if (format.GetLength() - index > 0)
			{
				stream.write(&(format[index]), format.GetLength() - index);
			}
			return String(stream.str().c_str());
		}

		// Members
	private:
		std::string m_Value;

		// Constructors
	public:
		String()
			: m_Value("")
		{

		}

		String(const char* value)
			: m_Value(value)
		{

		}

		// Override
	public:
		virtual String ToString() const override
		{
			return *this;
		}

		// Operators
	public:
		const char& operator[](SizeT index) const
		{
			return m_Value[index];
		}

		char& operator[](SizeT index)
		{
			return m_Value[index];
		}

		String& operator+=(const String& str)
		{
			m_Value += str.m_Value;
			return *this;
		}

		// Getters
	public:
		inline SizeT GetLength() const
		{
			return (SizeT)m_Value.length();
		}

		inline const char* GetPointer() const
		{
			return m_Value.c_str();
		}

		inline bool IsEmpty() const
		{
			return GetLength() == 0;
		}

		// Setters
	public:

		// Actions
	public:
		void Clear()
		{
			m_Value.clear();
		}

		int Find(char value, SizeT from = 0) const
		{
			SizeT to = GetLength();
			return Find(value, from, to);
		}

		int Find(char value, SizeT from, SizeT to) const
		{
			to = (to < GetLength()) ? to : GetLength() - 1;
			for (SizeT i = from; i <= to; i++)
			{
				if (m_Value[i] == value)
				{
					return i;
				}
			}
			return -1;
		}

		int Find(const String& value, SizeT from = 0) const
		{
			SizeT to = GetLength();
			return Find(value, from, to);
		}

		int Find(const String& value, SizeT from, SizeT to) const
		{
			to = (to < GetLength()) ? to : GetLength() - 1;
			to -= value.GetLength() - 1;

			for (SizeT i = from; i <= to; i++)
			{
				bool found = m_Value[i] == value[0];
				for (SizeT j = 1; j < value.GetLength() && found; j++)
				{
					found = m_Value[i + j] == value[j];
				}
				if (found)
				{
					return i;
				}
			}
			return -1;
		}
	};

	// Static Operators
	inline bool operator==(const String& a, const String& b)
	{
		return std::string(a.GetPointer()) == std::string(b.GetPointer());
	}

	inline bool operator!=(const String& a, const String& b)
	{
		return std::string(a.GetPointer()) != std::string(b.GetPointer());
	}

	inline String operator+(const String& a, const String& b)
	{
		return String((std::string(a.GetPointer()) + std::string(b.GetPointer())).c_str());
	}

	inline String operator+(const String& a, const char* b)
	{
		return String((std::string(a.GetPointer()) + std::string(b)).c_str());
	}

	inline String operator+(const char* a, const String& b)
	{
		return String((std::string(a) + std::string(b.GetPointer())).c_str());
	}

	inline String operator+(const String& a, const char b)
	{
		return String((std::string(a.GetPointer()) + b).c_str());
	}

	inline String operator+(const char a, const String& b)
	{
		return String((a + std::string(b.GetPointer())).c_str());
	}
}

namespace NewWorld
{
	using String = NewWorld::DataTypes::Collections::String;
}