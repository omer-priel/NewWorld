#include "nwpch.h"
#include "Type.h"

#include "NewWorld/DataTypes/Collections/String.h"

namespace NewWorld::DataTypes
{
	// Type
	const NewWorld::DataTypes::Type& Type::GetType() const
	{
		return NewWorld::DataTypes::TypeManager::GetType(0, "Type", "NewWorld::DataTypes");
	}

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

	// TypeManager
	Collections::Map<uint, Type> TypeManager::s_Types;

	const Type& TypeManager::GetType(uint staticId, const char* className, const char* namespaceFullName)
	{
		Collections::Map<uint, Type>::iterator it = s_Types.find(staticId);
		if (it != s_Types.end())
		{
			return it->second;
		}

		s_Types.insert({ staticId, Type(staticId, className, namespaceFullName) });
		return s_Types[staticId];
	}
}