#pragma once

#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/IObject.h"

#include "Dependencies.h"

namespace NewWorld::DataTypes
{
	class Type;
}

namespace NewWorld::DataTypes::Collections
{
	template <typename T>
	class BasicString : public IObject
	{
	//NW_CLASS(BasicString, NewWorld::DataTypes::Collections)

	// Members
	private:
		Ulong m_Length;
		T* m_Value; // TEMP

	public:
		BasicString()
			: m_Value(nullptr), m_Length(0)
		{

		}

		BasicString(const T* value, Ulong length) // TEMP
			: m_Length(length)
		{
			m_Value = new T[m_Length]; // TEMP

			std::memcpy(m_Value, value, m_Length); // TEMP
		}

		// Operators
	public:
		BasicString& operator=(const BasicString& other)
		{			
			m_Length = other.m_Length;
			m_Value = new T[m_Length]; // TEMP

			std::memcpy(m_Value, other.m_Value, m_Length); // TEMP
			return *this;
		}

		// Getters
	public:
		Ulong GetLength() const
		{
			return m_Length;
		}

		T* GetPointer() const // TEMP
		{
			return m_Value;
		}
	};
}