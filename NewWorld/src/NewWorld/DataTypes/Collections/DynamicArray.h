#pragma once

#include "NewWorld/DataTypes/Collections/BasicDynamicArray.h"

namespace NewWorld::DataTypes::Collections
{
	template <typename T>
	class DynamicArray : public BasicDynamicArray<T, SizeT, 1>
	{
		NW_CLASS(DynamicArray, NewWorld::DataTypes::Collections)

		// Constructors
	public:
		DynamicArray()
			: BasicDynamicArray<T, SizeT, 1>() { }

		DynamicArray(SizeT capacity)
			: BasicDynamicArray<T, SizeT, 1>(capacity) { }
	};
}