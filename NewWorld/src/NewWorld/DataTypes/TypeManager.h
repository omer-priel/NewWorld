#pragma once

#include "NewWorld/DataTypes/Type.h"
#include "NewWorld/DataTypes/Collections/DynamicArray.h"

namespace NewWorld::DataTypes
{
	class TypeManager
	{		
		// Static Members
	private:
		Collections::DynamicArray<Type> s_Types;

		// Static Getters
	public:
		static uint NameToStaticTypeID(const char* className, const char* namespaceFullName)
		{
			return 0;
		}

		static const Type& GetTypeByName(const char* className, const char* namespaceFullName)
		{
			uint staticId = NameToStaticTypeID(className, namespaceFullName);
			s_Types.push_back(Type(staticId, className, namespaceFullName));
		}

		static const Type& GetTypeByStaticID(const uint id)
		{

		}
	};
}