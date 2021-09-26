#pragma once

#include "NewWorld/DataTypes/Collections/BasicArray.h"

namespace NewWorld::DataTypes::Collections
{
	template <typename T, const SizeT LENGTH>
	class Array : public BasicArray<T, SizeT, LENGTH>
	{
		NW_CLASS(Array, NewWorld::DataTypes::Collections)

		// Constructors
	public:
		template<typename... Types>
		Array(Types&&... elements)
			: BasicArray<T, SizeT, LENGTH>(elements...) { }
	};
}