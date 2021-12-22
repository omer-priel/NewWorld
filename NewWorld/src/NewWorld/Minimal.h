#pragma once

// Macros
#include "NewWorld/Macros.h"

// Standard Template Library
#include <utility>

// DataTypes
#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/Object.h"
#include "NewWorld/DataTypes/Memory/Allocator.h"
#include "NewWorld/DataTypes/Memory/RawPointer.h"
#include "NewWorld/DataTypes/Memory/ScopePointer.h"
#include "NewWorld/DataTypes/Memory/SharedPointer.h"
#include "NewWorld/DataTypes/Collections/Array.h"
#include "NewWorld/DataTypes/Collections/DynamicArray.h"

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

	template <typename T, const SizeT LENGTH>
	using Array = DataTypes::Collections::Array<T, LENGTH>;
	template <typename T>
	using DynamicArray = DataTypes::Collections::DynamicArray<T>;
}

// Math
// TODO: Move affter Debug
#include "NewWorld/Math/Vector2.h"
#include "NewWorld/Math/Vector3.h"
#include "NewWorld/Math/Vector4.h"
#include "NewWorld/Math/Matrix2.h"
#include "NewWorld/Math/Matrix3.h"
#include "NewWorld/Math/Matrix4.h"

namespace NewWorld
{
	using Vector2 = Math::Vector2;
	using Vector3 = Math::Vector3;
	using Vector4 = Math::Vector4;

	using Matrix2 = Math::Matrix2;
	using Matrix3 = Math::Matrix3;
	using Matrix4 = Math::Matrix4;
}

// Debug
#include "NewWorld/Debug/LoggerOld.h"
#include "NewWorld/Debug/Logger.h"