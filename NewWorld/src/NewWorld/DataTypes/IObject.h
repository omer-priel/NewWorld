#pragma once

#include "NewWorld/Macros.h"
#include "NewWorld/DataTypes/Primitives.h"

namespace NewWorld::DataTypes
{
	// Declarations
	class Type;
	
	namespace Collections
	{
		class String;
	}

	// IObject
	class IObject abstract
	{
		// Pure virtual functions
	public:
		virtual Collections::String ToString() const = 0;
		
		virtual Type& GetType() const = 0;
	};
}
