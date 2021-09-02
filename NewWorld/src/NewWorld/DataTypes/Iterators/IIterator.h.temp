#pragma once

#include "Engine/Core.h"

namespace Engine::DataTypes::Iterators
{
	template <typename Iterator_T>
	class IIterator
	{
	public:
		virtual Iterator_T GetIterator() = 0;
		virtual Iterator_T GetEndIterator() = 0;

		inline Iterator_T begin()
		{
			return GetIterator();
		}

		inline Iterator_T end()
		{
			return GetEndIterator();
		}
	};
}