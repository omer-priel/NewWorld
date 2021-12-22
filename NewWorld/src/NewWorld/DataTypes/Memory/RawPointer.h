#pragma once

#include "NewWorld/DataTypes/Memory/Allocator.h"

namespace NewWorld::DataTypes::Memory
{
	template <typename T>
	using RawPointer = T*;
}