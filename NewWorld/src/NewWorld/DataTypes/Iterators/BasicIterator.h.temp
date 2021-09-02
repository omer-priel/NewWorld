#pragma once

#include "Engine/Core.h"

namespace Engine::DataTypes::Iterators
{
	template<typename T, typename Iterator_T>
	class BasicIterator : public DataTypes::Object
	{
		// Virtual functions
	public:
		virtual Iterator_T& operator++() = 0;
		virtual Iterator_T& operator++(int) = 0;

		virtual bool operator==(const Iterator_T& other) = 0;

		virtual bool operator!=(const Iterator_T& other)
		{
			return !(*this == other);
		}
	};
}
