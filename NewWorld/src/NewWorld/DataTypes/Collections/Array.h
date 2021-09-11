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
		Array(T&& value)
			: BasicArray<T, SizeT, LENGTH>((T&&)value) { }

		template <typename... Types>
		Array(Types&&... args)
			: BasicArray<T, SizeT, LENGTH>(args...)
		{
			
		}
	};
}