#pragma once

#include "BasicString.h"
#include "NewWorld/DataTypes/Type.h"

#include <Dependencies.h>

namespace NewWorld::DataTypes::Collections
{
	class String : public BasicString<char>
	{
	NW_CLASS(String, NewWorld::DataTypes::Collections)

	public:
		String()
			: BasicString("", 0)
		{

		}

		String(const char* value)
			: BasicString<char>(value, strlen(value))
		{

		}

		// Override
	public:
		virtual String ToString() const override
		{
			return *this;
		}
	};
}

namespace NewWorld
{
	using String = NewWorld::DataTypes::Collections::String;
}