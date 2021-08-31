#pragma once

#include "Engine/Core.h"

#include "Engine/DataTypes/Iterators/FullAccessForwardIterator.h"
#include "Engine/DataTypes/Iterators/BidirectionalIterator.h"

namespace Engine::DataTypes::Iterators
{
	template<typename T, typename Iterator_T, typename Length_T>
	class FullAccessIterator : public FullAccessForwardIterator<T, Iterator_T, Length_T>, public BidirectionalIterator<T, Iterator_T>
	{
		// Virtual functions
	public:
		virtual Iterator_T& operator-=(const Length_T& value) = 0;
	};
}