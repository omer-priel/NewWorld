#pragma once

#include "Engine/Core.h"

#include "Engine/DataTypes/Iterators/ForwardIterator.h"

namespace Engine::DataTypes::Iterators
{
	template<typename T, typename Iterator_T, typename Length_T>	
	class FullAccessForwardIterator : public ForwardIterator<T, Iterator_T>
	{
		// Virtual functions
	public:
		virtual Iterator_T& operator+=(const Length_T& value) = 0;
	};
}