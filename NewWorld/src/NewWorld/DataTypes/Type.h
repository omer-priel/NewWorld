#pragma once

#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/IObject.h"

#include "Dependencies.h"

namespace NewWorld::DataTypes
{
	namespace Collections
	{
		class String;
	}

	class Type : public IObject
	{
	NW_CLASS(Type, NewWorld::DataTypes)		  
		// Static
	public:
		static const Type GetTypeByName(const char* className, const char* namespaceFullName)
		{
			// TODO: Need Type Cash System to save all the Types
			// TODO: Generate Type IDs
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

		// Override
	public:
		Collections::String ToString() const override;

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
			
			char* fullName = new char[str.length()];
			std::memcpy(fullName, str.c_str(), str.length());
			
			// FIX: Memory Leak

			return fullName;
		}
	};
}