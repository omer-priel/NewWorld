#pragma once

#include "NewWorld/DataTypes/Object.h"

namespace NewWorld::DataTypes::Memory
{
	template<typename T>
	class IPointer abstract : public Object
	{
	NW_CLASS(IPointer<T>, NewWorld::DataTypes::Memory)

		// Pure virtual functions
	public:
		virtual T* operator->() const = 0;

		virtual T& operator*() = 0;

		virtual const T& operator*() const = 0;
	};
}