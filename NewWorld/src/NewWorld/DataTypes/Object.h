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
	public:
		NW_CLASS(Object, NewWorld::DataTypes)

	public:
		virtual ~Object() { };
	
	// Override
	public:
		virtual String ToString() const override
		{
			// TODO if (T is IObject) else if (T Is primitive) else ERROR
			return String();
		}
	};
}