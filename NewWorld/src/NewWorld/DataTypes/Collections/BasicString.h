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
	public:
		T* m_Value;

	public:
		BasicString()
			: m_Value(nullptr)
		{

		}

		BasicString(const T* value) // TEMP
		{
			Ulong size = sizeof(value) * sizeof(T);
			m_Value = (T*)alloca(size); // TEMP
			
			std::memcpy(m_Value, value, size); // TEMP
		}
	};
}