#pragma once

#include "NewWorld/DataTypes/Memory/IPointer.h"

namespace NewWorld::DataTypes::Memory
{
	template <typename T>
	class ScopePointer : public IPointer<T>
	{
	NW_CLASS(ScopePointer, NewWorld::DataTypes::Memory)

	private:
		T* m_Value;

	public:
		ScopePointer()
		{
			m_Value = new T();
		}

		ScopePointer(const T& value)
		{
			m_Value = new T(value);
		}

		ScopePointer(T&& value)
		{
			m_Value = new T(value);
		}

		template <typename... Types>
		ScopePointer(Types&&... args)
		{
			m_Value = new T(std::forward<Types>(args)...);
		}

		ScopePointer(ScopePointer& obj) = delete;

		~ScopePointer()
		{
			delete m_Value;
		}

		// Operators
		virtual T* operator->() const override { return m_Value; }

		virtual T& operator*() override { return *m_Value; }

		virtual const T& operator*() const override { return *m_Value; }
	};
}