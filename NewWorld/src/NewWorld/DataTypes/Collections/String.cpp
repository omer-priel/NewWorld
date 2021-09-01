#include "nwpch.h"
#include "String.h"

namespace NewWorld::DataTypes::Collections
{
	NewWorld::DataTypes::Type String::GetType() const
	{
		return NewWorld::DataTypes::Type::GetTypeByName("String", "NewWorld::DataTypes::Collections");
	}
}