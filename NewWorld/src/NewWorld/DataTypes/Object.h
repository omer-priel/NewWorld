#pragma once

#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/IObject.h"
#include "NewWorld/DataTypes/Type.h"
#include "NewWorld/DataTypes/Collections/String.h"

namespace NewWorld::DataTypes
{
	class Object : DataTypes::IObject
	{
	NW_CLASS(Object, NewWorld::DataTypes)

	public:
		virtual ~Object() { };
	
	// Override
	public:
		Collections::String ToString() const override;
	};
}