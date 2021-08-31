#pragma once

#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/IObject.h"

#include "Dependencies.h"

namespace NewWorld::DataTypes::Collections
{
	template <typename T>
	class BasicString // : public DataTypes::IObject
	{
	// Members
	private:
		Ulong m_Size;
		T* m_Value; // TEMP

	public:
		BasicString()
			: m_Value(nullptr), m_Size(0)
		{

		}

		BasicString(const T* value, Ulong size) // TEMP
			: m_Size(size)
		{
			m_Value = (T*)alloca(m_Size); // TEMP

			std::memcpy(m_Value, value, m_Size); // TEMP
		}

		// Operators
	public:
		BasicString& operator=(const BasicString& other)
		{			
			m_Size = other.m_Size;
			m_Value = (T*)alloca(m_Size); // TEMP

			std::memcpy(m_Value, other.m_Value, m_Size); // TEMP
			return *this;
		}

		// Getters
	public:
		Ulong GetSize() const
		{
			return m_Size;
		}

		T* GetPointer() const // TEMP
		{
			return m_Value;
		}
	};
}