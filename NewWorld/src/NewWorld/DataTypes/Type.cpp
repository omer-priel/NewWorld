#include "nwpch.h"
#include "Type.h"

#include "NewWorld/DataTypes/Collections/String.h"

namespace NewWorld::DataTypes
{
	Collections::String Type::ToString() const
	{
		return Collections::String(GetType().GetFullName());
	}
}