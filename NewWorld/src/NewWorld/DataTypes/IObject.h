#pragma once

#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/Type.h"

namespace NewWorld::DataTypes
{
	// Declarations
	namespace Collections
	{
		class String;
	}

	// IObject
	class IObject abstract
	{
		// Pure functions
	public:
		virtual Collections::String ToString() const = 0;
		
		virtual Type GetType() const = 0;
	};
}
