#pragma once

#include "NewWorld/DataTypes/Primitives.h"
#include "NewWorld/DataTypes/IObject.h"

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
		static const Type& GetTypeByName(const char* className, const char* namespaceFullName)
		{
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
		inline SizeT GetID() const
		{
			return m_ID;
		}

		inline const char* GetName() const
		{
			return m_Name;
		}

		inline const char* GetNamespaceFullName() const
		{
			return m_NamespaceFullName;
		}

		const char* GetFullName() const;
	};
}