#pragma once

// This is Core class

#include "Engine/DataTypes/Primitives.h"
#include "Engine/DataTypes/IObject.h"

namespace Engine::DataTypes::Collections
{
	template <typename T>
	class BasicString : public DataTypes::IObject
	{
	// Members
	public:
		const T* m_Value = "TODO";

	public:
		BasicString() {}
	};
}