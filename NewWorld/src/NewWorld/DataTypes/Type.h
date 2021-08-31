#pragma once

#include "NewWorld/DataTypes/Primitives.h"

#include "Dependencies.h"

#define NW_CLASS(className, namespaceFullName) public: NewWorld::DataTypes::Type GetType() const override { return NewWorld::DataTypes::Type::GetType(#className, #namespaceFullName); }

namespace NewWorld::DataTypes
{
	class Type
	{
		// Static
	public:
		static const Type GetType(const char* className, const char* namespaceFullName)
		{
			// TODO: Need Type Cash System to save all the Types
			SizeT id = 0;
			return Type(id, className, namespaceFullName);
		}

		// Members
	private:
		SizeT m_ID;
		const char* m_Name;
		const char* m_NamespaceFullName;

		// Constractors
	private:
		Type(SizeT id, const char* name, const char* namespaceFullName)
			: m_ID(id), m_Name(name), m_NamespaceFullName(namespaceFullName)
		{

		}

		// Getters
	public:
		SizeT GetID() const
		{
			return m_ID;
		}

		const char* GetName() const
		{
			return m_Name;
		}

		const char* GetNamespaceFullName() const
		{
			return m_NamespaceFullName;
		}

		const char* GetFullName() const
		{
			std::string str = ((std::string)m_NamespaceFullName + (std::string)"::" + (std::string)m_Name);
			
			char* fullName = new char[str.length() + 1];
			std::strcpy(fullName, str.c_str());
			
			// FIX: Memory Leak

			return fullName;
		}
	};
}