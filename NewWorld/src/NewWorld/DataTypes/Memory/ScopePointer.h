#pragma once

#include "NewWorld/DataTypes/Memory/IPointer.h"
#include "NewWorld/DataTypes/Memory/Allocator.h"

namespace NewWorld::DataTypes::Memory
{
	template <typename T>
	class ScopePointer : public IPointer<T>
	{
	NW_CLASS(ScopePointer, NewWorld::DataTypes::Memory)

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

		~ScopePointer()
		{
			delete m_Value;
		}

		// Operators
		ScopePointer& operator= (const ScopePointer& obj) = delete;

		virtual T* operator->() const override { return m_Value; }

		virtual T& operator*() override { return *m_Value; }

		virtual const T& operator*() const override { return *m_Value; }
	};
}