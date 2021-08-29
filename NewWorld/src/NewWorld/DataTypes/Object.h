#pragma once

// This is Core class

#include "Engine/DataTypes/Primitives.h"
#include "Engine/DataTypes/IObject.h"
#include "Engine/DataTypes/Collections/String.h"

namespace Engine::DataTypes
{
	using String = Engine::DataTypes::Collections::String;

	class Object : DataTypes::IObject
	{
	// Static
	public:
		template<typename T>
		String ToString(const T& object)
		{
			// TODO if (T is IObject) else if (T Is primitive) else ERROR
			return String();
		}

	protected:
		virtual ~Object() { };
	
	// Override
	public:
		virtual String ToString() const override
		{
			return String();
		}
	};
}