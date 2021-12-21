#pragma once

#include <map>

namespace NewWorld::DataTypes::Collections
{
	template <typename KEY_T, typename T>
	using Map = std::map<KEY_T, T>;
}