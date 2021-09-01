#pragma once

// BuildFlags
#include "NewWorld/Core/BuildFlags.h"

// DataTypes
#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/Object.h"

namespace NewWorld
{
	using Byte = DataTypes::Byte;
	using ushort = DataTypes::ushort;
	using uint = DataTypes::uint;
	using Long = DataTypes::Long;
	using Ulong = DataTypes::Ulong;
	using SizeT = DataTypes::SizeT;

	using IObject = DataTypes::IObject;
	using Object = DataTypes::Object;
}

// Debug
#include "NewWorld/Debug/Logger.h"