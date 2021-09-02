#pragma once

#include "Engine/Core.h"

#include "Engine/DataTypes/Iterators/ReadIterator.h"

namespace Engine::DataTypes::Iterators
{
	template<typename T, typename Iterator_T>
	class ForwardIterator : public ReadIterator<T, Iterator_T>
	{
		// Virtual functions
	public:
		virtual T& operator*() = 0;
	};
}