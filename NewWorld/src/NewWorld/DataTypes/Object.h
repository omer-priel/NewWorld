#pragma once

#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/Build/TypeID.h"
#include "NewWorld/DataTypes/IObject.h"
#include "NewWorld/DataTypes/Type.h"
#include "NewWorld/DataTypes/Collections/String.h"

namespace NewWorld::DataTypes
{
	class Object : public DataTypes::IObject
	{
	NW_CLASS(Object, NewWorld::DataTypes)
	
	// Override
	public:
		Collections::String ToString() const override;
	};
}