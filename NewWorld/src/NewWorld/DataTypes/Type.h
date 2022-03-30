#pragma once

#include "NewWorld/DataTypes/IObject.h"
#include "NewWorld/DataTypes/Collections/Map.h"

namespace NewWorld::DataTypes
{
	namespace Collections
	{
		class String;
	}

	class Type : virtual public IObject
	{	
	public:
		const NewWorld::DataTypes::Type& GetType() const override;
		
		// Members
	private:
		uint m_StaticID;
		const char* m_Name;
		const char* m_NamespaceFullName;

		// Constractors
	public:
		Type()
			: m_StaticID(0), m_Name(""), m_NamespaceFullName("") { }

		Type(uint staticId, const char* name, const char* namespaceFullName)
			: m_StaticID(staticId), m_Name(name), m_NamespaceFullName(namespaceFullName)
		{

		}

		// Override
	public:
		Collections::String ToString() const override;

		// Getters
	public:
		inline SizeT GetStaticID() const
		{
			return m_StaticID;
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

	class TypeManager
	{
		// Static Members
	private:
		static Collections::Map<uint, Type> s_Types;

		// Static Getters
	public:
		static const Type& GetType(uint staticId, const char* className, const char* namespaceFullName);

		static const Type& GetTypeByStaticID(const uint staticId)
		{
			return s_Types[staticId];
		}

		template<typename T>
		static const Type& GetType()
		{
			return s_Types[NW_TYPE_ID(T)];
		}
	};
}