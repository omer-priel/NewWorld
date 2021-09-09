#pragma once

// Macros
#include "NewWorld/Macros.h"

// DataTypes
#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/Object.h"
#include "NewWorld/DataTypes/Memory/RawPointer.h"
#include "NewWorld/DataTypes/Memory/ScopePointer.h"
#include "NewWorld/DataTypes/Memory/SharedPointer.h"

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

	template <typename T>
    using RawPointer = DataTypes::Memory::RawPointer<T>;
	template <typename T>
	using ScopePointer = DataTypes::Memory::ScopePointer<T>;
	template <typename T>
	using SharedPointer = DataTypes::Memory::SharedPointer<T>;
}

// Debug
#include "NewWorld/Debug/Logger.h"