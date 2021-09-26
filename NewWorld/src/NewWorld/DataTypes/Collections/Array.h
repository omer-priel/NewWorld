#pragma once

#include "NewWorld/DataTypes/Object.h"

#include <array>

namespace NewWorld::DataTypes::Collections
{
	template <typename T, const SizeT LENGTH>
	using Array = std::array<T, LENGTH>;
}