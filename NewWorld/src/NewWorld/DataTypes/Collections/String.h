#pragma once

#include "NewWorld/DataTypes/IObject.h"
#include "NewWorld/DataTypes/Type.h"

#include <string>

namespace NewWorld::DataTypes::Collections
{
	class String : public IObject
	{
	NW_CLASS(String, NewWorld::DataTypes::Collections)

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