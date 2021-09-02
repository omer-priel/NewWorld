#include "nwpch.h"
#include "Object.h"

namespace NewWorld::DataTypes
{
	Collections::String Object::ToString() const
	{
		return Collections::String(GetType().GetFullName());
	}
}