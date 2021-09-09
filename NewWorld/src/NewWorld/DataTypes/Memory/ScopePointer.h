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
			: m_Value(nullptr)
		{

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
			if (m_Value != nullptr)
			{
				delete m_Value;
			}
		}

		// Getters
		inline bool HasValue() const { return m_Value != nullptr; }

		const T& GetValue() const
		{
			NW_ASSERT(HasValue(), "Can't read nullptr!");

			return *m_Value;
		}

		// Setters
		void SetValue(const T& value)
		{
			if (HasValue())
			{
				*m_Value = value;
			}
			else
			{
				m_Value = new T(value);
			}
		}

		void SetValue(T&& value)
		{
			if (HasValue())
			{
				*m_Value = value;
			}
			else
			{
				m_Value = new T(value);
			}
		}

		// Operators
		inline operator T& () { return *m_Value; };

		inline operator const T& () const { return *m_Value; };
	};
}