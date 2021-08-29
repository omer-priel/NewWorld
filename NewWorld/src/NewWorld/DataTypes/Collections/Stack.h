#pragma once

#include "Engine/Core.h"
#include "Engine/DataTypes/Collections/BasicStack.h"

namespace Engine::DataTypes::Collections
{
	template <typename T>
	class Stack : public BasicStack<T>
	{

	};
}