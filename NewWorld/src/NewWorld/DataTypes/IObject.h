#pragma once

#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/Type.h"

#define NW_DEFUALT_TO_STRING() public: NewWorld::DataTypes::Collections::String ToString() const override { return NewWorld::DataTypes::Collections::String(GetType().GetFullName()); }

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
