#pragma once

// This is Core class

#include "Engine/DataTypes/Primitives.h"

namespace Engine::DataTypes
{
	namespace Collections
	{
		class String;
	}

	using String = Engine::DataTypes::Collections::String;

	class IObject abstract
	{
	public:
		virtual String ToString() const = 0;
	};
}
