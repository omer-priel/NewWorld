#pragma once

#include "NewWorld/DataTypes/Primitives.h"

namespace NewWorld::DataTypes
{
	namespace Collections
	{
		class String;
	}

	using String = NewWorld::DataTypes::Collections::String;

	class IObject abstract
	{
	public:
		virtual String ToString() const = 0;
	};
}
