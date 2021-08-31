#pragma once

#include "BasicString.h"

#include <Dependencies.h>

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

	// TODO: Replace with proper code
	std::ostream& operator<<(std::ostream& os, const String& obj)
	{
		os << obj.m_Value;
		return os;
	}
}