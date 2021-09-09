#pragma once

#include "NewWorld/DataTypes/Memory/IPointer.h"

namespace NewWorld::DataTypes::Memory
{
	template <typename T>
	class SharedPointer : public IPointer<T>
	{
	NW_CLASS(SharedPointer, NewWorld::DataTypes::Memory)

	private:
		T* m_Value;

		SizeT* m_Counter;

	public:
		SharedPointer()
		{
			m_Value = new T();
			m_Counter = new SizeT(1);
		}

		SharedPointer(const T& value)
		{
			m_Value = new T(value);
			m_Counter = new SizeT(1);
		}

		SharedPointer(T&& value)
		{
			m_Value = new T(value);
			m_Counter = new SizeT(1);
		}

		SharedPointer(SharedPointer& obj)
		{
			m_Value = obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
		}

		~SharedPointer()
		{
			(*m_Counter)--;
			if (m_Counter == 0)
			{
				delete m_Value;
				delete m_Counter;
			}
		}

		// Operators
		virtual T* operator->() const override { return m_Value; }

		virtual T& operator*() override { return *m_Value; }

		virtual const T& operator*() const override { return *m_Value; }
	};
}