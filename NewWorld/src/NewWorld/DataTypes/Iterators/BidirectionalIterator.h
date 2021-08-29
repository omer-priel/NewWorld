#pragma once

#include "Engine/Core.h"

#include "Engine/DataTypes/Iterators/ForwardIterator.h"

namespace Engine::DataTypes::Iterators
{
	template<typename T, typename Iterator_T>
	class BidirectionalIterator : public ForwardIterator<T, Iterator_T>
	{
		// Virtual functions
	public:
		virtual Iterator_T& operator--() = 0;
		virtual Iterator_T& operator--(int) = 0;
	};
}