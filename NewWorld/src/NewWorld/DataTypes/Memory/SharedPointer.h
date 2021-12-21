#pragma once

#include "NewWorld/DataTypes/Memory/IPointer.h"
#include "NewWorld/DataTypes/Memory/Allocator.h"

#include <iostream>
#include <string>

namespace NewWorld::DataTypes::Memory
{
	template <typename T>
	class SharedPointer : public IPointer<T>
	{
	NW_CLASS(SharedPointer<T>, NewWorld::DataTypes::Memory)

	private:
		T* m_Value;
		uint* m_Counter;

	public:
		SharedPointer(const SharedPointer& obj)
		{
			m_Value = obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
		}

		SharedPointer(SharedPointer& obj)
		{
			m_Value = obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
		}
		
		template <typename... Types>
		SharedPointer(Types&&... args)
		{
			m_Value = new T(std::forward<Types>(args)...);
			m_Counter = new SizeT(1);
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
		SharedPointer& operator= (const SharedPointer& obj)
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