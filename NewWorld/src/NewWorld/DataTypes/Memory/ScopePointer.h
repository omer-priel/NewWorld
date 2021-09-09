#pragma once

#include "NewWorld/DataTypes/Memory/IPointer.h"

namespace NewWorld::DataTypes::Memory
{
	template <typename T>
	class ScopePointer : public IPointer
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

		ScopePointer(ScopePointer& obj) = delete;

		~ScopePointer()
		{
			delete m_Value;
		}

		// Operators
		T* operator->() const { return m_Value; }

		T& operator*() { return *m_Value; }

		const T& operator*() const { return *m_Value; }
	};
}