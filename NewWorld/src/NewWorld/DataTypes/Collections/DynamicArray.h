#pragma once

#include "Engine/Core.h"
#include "Engine/DataTypes/Collections/BasicDynamicArray.h"

namespace Engine::DataTypes::Collections
{
	template <typename T>
	class DynamicArray : public BasicDynamicArray<T, SizeT, 1>
	{

	};
}