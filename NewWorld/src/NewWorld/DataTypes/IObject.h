#pragma once

#include "NewWorld/DataTypes/Primitives.h"

#define NW_CLASS(className, namespaceFullName) public: NewWorld::DataTypes::Type GetType() const override { return NewWorld::DataTypes::Type::GetTypeByName(#className, #namespaceFullName); }

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
		// Pure functions
	public:
		virtual Collections::String ToString() const = 0;
		
		virtual Type GetType() const = 0;
	};
}
