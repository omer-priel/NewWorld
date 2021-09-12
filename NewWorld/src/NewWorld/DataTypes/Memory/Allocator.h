#pragma once

#include "NewWorld/DataTypes/Object.h"

namespace NewWorld::DataTypes::Memory
{
	class Allocator : public Object
	{
	NW_CLASS(Allocator, NewWorld::DataTypes::Memory)

	public:
		Allocator()
		{

		}

		// Actions
	public:
		void* Allocate(uint size)
		{

		}

		template <typename T>
		T* Allocate()
		{
			return (T*)Allocate(sizeof(T));
		}
	};
}
