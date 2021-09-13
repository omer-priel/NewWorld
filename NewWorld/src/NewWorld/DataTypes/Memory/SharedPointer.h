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

		uint* m_Counter;

	public:
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

		template <typename... Types>
		SharedPointer(Types&&... args)
		{
			m_Value = new T(std::forward<Types>(args)...);
			m_Counter = new SizeT(1);
		}

		SharedPointer(const SharedPointer& obj)
		{
			m_Value = obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
		}

		virtual ~SharedPointer()
		{
			(*m_Counter)--;
			if (*m_Counter == 0)
			{
				delete m_Value;
				delete m_Counter;
			}
		}

		// Operators
		SharedPointer<T>& operator= (const SharedPointer<T>& obj)
		{
			if (m_Counter != nullptr)
			{
				this->~SharedPointer();
			}
			m_Value = obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
			return *this;
		}

		virtual T* operator->() const override { return m_Value; }

		virtual T& operator*() override { return *m_Value; }

		virtual const T& operator*() const override { return *m_Value; }
	};
}