#pragma once

#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/IObject.h"

namespace NewWorld::DataTypes::Collections
{
	template <typename T>
	class BasicString : public DataTypes::IObject
	{
	// Members
	public:
		const T* m_Value = "DEFUALT";

	public:
		BasicString() {}
	};
}