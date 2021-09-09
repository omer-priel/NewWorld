#pragma once

#include "NewWorld/DataTypes/Memory/IPointer.h"

namespace NewWorld::DataTypes::Memory
{
	template <typename T>
	using RawPointer = T*;
}