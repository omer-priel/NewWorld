#pragma once

#include "NewWorld/DataTypes/IObject.h"
#include "NewWorld/DataTypes/Type.h"
#include "NewWorld/DataTypes/Collections/String.h"

namespace NewWorld::DataTypes
{
	class Object : public DataTypes::IObject
	{
	NW_CLASS(NewWorld::DataTypes, Object)
	
	// Override
	public:
		Collections::String ToString() const override;
	};
}