#include "nwpch.h"
#include "Type.h"

#include "NewWorld/DataTypes/Collections/String.h"

namespace NewWorld::DataTypes
{
	Collections::String Type::ToString() const
	{
		return Collections::String(GetFullName());
	}

	const char* Type::GetFullName() const
	{
		std::string str = ((std::string)m_NamespaceFullName + (std::string)"::" + (std::string)m_Name);

		char* fullName = new char[str.length() + 1];
		std::memcpy(fullName, str.c_str(), str.length());
		fullName[str.length()] = '\0';

		// FIX: Memory Leak

		return fullName;
	}
}