#pragma once

// This is Core class

#include "BasicString.h"

namespace NewWorld::DataTypes::Collections
{
	class String : public BasicString<char>
	{
		// Override
	public:
		virtual String ToString() const override
		{
			return *this;
		}
	};
}