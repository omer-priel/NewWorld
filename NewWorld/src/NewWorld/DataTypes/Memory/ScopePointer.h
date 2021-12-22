#pragma once

#include "NewWorld/DataTypes/Memory/IPointer.h"
#include "NewWorld/DataTypes/Memory/Allocator.h"

namespace NewWorld::DataTypes::Memory
{
	template <typename T>
	class ScopePointer : public IPointer<T>
	{
	NW_CLASS(NewWorld::DataTypes::Memory, ScopePointer<T>)

	private:
		T* m_Value;

	public:
		ScopePointer(const ScopePointer& obj) = delete;

		ScopePointer(ScopePointer& obj) = delete;

		template <typename... Types>
		ScopePointer(Types&&... args)
		{
			m_Value = new T(std::forward<Types>(args)...);
		}

		virtual ~ScopePointer()
		{
			delete m_Value;
		}

		// Override
	public:
		String ToString() const override
		{
			if (std::is_base_of<IObject, T>())
			{
				RawPointer<IObject> obj = (RawPointer<IObject>)m_Value;
				return obj->ToString();
			}
			return "";
		}

		// Operators
		ScopePointer& operator= (const ScopePointer& obj) = delete;

		virtual T* operator->() const override { return m_Value; }

		virtual T& operator*() override { return *m_Value; }

		virtual const T& operator*() const override { return *m_Value; }
	};
}