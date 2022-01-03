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
		inline String ConverToString() { return ""; }

		inline String ConverToString(char value)
		{
			return String(value + "");
		}

		inline String ConverToString(Byte value)
		{
			return String(value + "");
		}

		inline String ConverToString(bool value)
		{
			return String((value) ? "true" : "false");
		}

		inline String ConverToString(short value)
		{
			return String(value + "");
		}

		inline String ConverToString(ushort value)
		{
			return String(value + "");
		}

		inline String ConverToString(int value)
		{
			return String(value + "");
		}

		inline String ConverToString(uint value)
		{
			return String(value + "");
		}

		inline String ConverToString(Long value)
		{
			return String(value + "");
		}

		inline String ConverToString(Ulong value)
		{
			return String(value + "");
		}

		inline String ConverToString(float value)
		{
			return String(std::to_string(value).c_str());
		}

		// TEMP: Enums
		inline String ConverToString(Debug::LogLevel value)
		{
			return String((int)value + "");
		}

		// TEMP: Vector2 Vector3 Vector4
		inline String ConverToString(Vector2 value)
		{
			return String::Format("({}, {})", value.x, value.y);
		}

		inline String ConverToString(Vector3 value)
		{
			return String::Format("({}, {}, {}, {})", value.x, value.y, value.z);
		}

		inline String ConverToString(Vector4 value)
		{
			return String::Format("({}, {}, {}, {})", value.x, value.y, value.z, value.w);
		}

		inline String ConverToString(const char* str)
		{
			return String(str);
		}

		inline String ConverToString(const String& str)
		{
			return str;
		}

		inline String ConverToString(const IObject& obj)
		{
			return obj.ToString();
		}

		template <typename T>
		inline String ConverToString(T* ptr)
		{
			if (ptr == nullptr)
			{
				return String("null");
			}
			else
			{
				return ConverToString((const T&)*ptr);
			}
		}

		template<typename... Types>
		static Array<String, (SizeT)sizeof...(Types)> ConverToString(const Types&... args)
		{
			const SizeT LENGTH = (SizeT)sizeof...(Types);
			Array<String, LENGTH> arr;
			for (size_t i = 0; i < LENGTH; i++)
			{
				if (std::is_base_of<IObject, Types[i]>::value)
				{
					arr[i] = ConverToString((const IObject&)args[i]);
				}
				else
				{
					arr[i] = ConverToString(args[i]);
				}
			}

			return arr;
		}
		
		// Static
	public:
		template<typename... Types>
		static String Format(String format, const Types&... args)
		{
			return String(std::format(format.m_Value.c_str(), args...).c_str());
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