#pragma once

#include "Engine/Core.h"
#include "Engine/DataTypes/Collections/BasicList.h"

namespace Engine::DataTypes::Collections
{
	template <typename T>
	class List : public BasicList<T, SizeT>
	{

	};
}