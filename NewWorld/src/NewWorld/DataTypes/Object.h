#pragma once

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
		String ToString() const override
		{
			return String(GetType().GetFullName());
		}
	};
}