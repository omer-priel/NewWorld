#pragma once

#include "NewWorld/DataTypes/Primitives.h"

namespace NewWorld::DataTypes
{
	// Declarations
	namespace Collections
	{
		class String;
	}

	// Aliases
	using String = NewWorld::DataTypes::Collections::String;

	// IObject
	class IObject abstract
	{
		// Pure functions
	public:
		virtual String ToString() const = 0;
	};
}
