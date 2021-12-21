#pragma once

#include "NewWorld/DataTypes/Primitives.h"

namespace NewWorld::DataTypes::Build
{
	inline uint c_LastTypeId = 0;
	template< typename T > inline const uint TypeIDStorage = c_LastTypeId++;
}