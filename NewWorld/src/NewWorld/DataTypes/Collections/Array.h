#pragma once

#include "NewWorld/DataTypes/Collections/BasicArray.h"

namespace NewWorld::DataTypes::Collections
{
	template <typename T, const SizeT LENGTH>
	using Array = BasicArray<T, SizeT, LENGTH>;
}