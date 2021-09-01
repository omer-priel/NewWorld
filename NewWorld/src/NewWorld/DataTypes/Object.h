#pragma once

// This is Core class

#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/IObject.h"
#include "NewWorld/DataTypes/Collections/String.h"

namespace NewWorld::DataTypes
{
	using String = NewWorld::DataTypes::Collections::String;

	class Object : DataTypes::IObject
	{
		NW_CLASS(Object, NewWorld::DataTypes)

	public:
		virtual ~Object() { };
	
	// Override
	public:
		
		NW_DEFUALT_TO_STRING()
	};
}