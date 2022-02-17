#pragma once

#include "NewWorld/DataTypes/Memory/IPointer.h"
#include "NewWorld/DataTypes/Memory/Allocator.h"

#include <type_traits>
#include <iostream>
#include <string>

namespace NewWorld::DataTypes::Memory
{
	// nullable SharedPointer
	template <typename T, const bool NULLABLE>
	class SharedPointer : public IPointer<T>
	{
		NW_CLASS(NewWorld::DataTypes::Memory, SharedPointer<T, true>)

		// Friends
	private:
		template<typename OtherT, const bool OtherNULLABLE>
		friend class SharedPointer;

	private:
		T* m_Value = nullptr;
		uint* m_Counter = nullptr;

	public:
		SharedPointer()
		{
			m_Value = nullptr;
			m_Counter = new SizeT(0);
		}

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

		template<typename OtherType>
		SharedPointer(const SharedPointer<OtherType, true>& obj)
		{
			m_Value = (T*)obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
		}

		template<typename OtherType>
		SharedPointer(SharedPointer<OtherType, true>& obj)
		{
			m_Value = (T*)obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
		}

		template <typename... Types>
		SharedPointer(Types... args)
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
			m_Value = (T*)obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
			return *this;
		}


		template<typename OtherType>
		SharedPointer& operator= (const SharedPointer<OtherType, true>& obj)
		{
			if (m_Counter != nullptr)
			{
				this->~SharedPointer();
			}
			m_Value = (T*)obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
			return *this;
		}

		virtual T* operator->() const override { return m_Value; }

		virtual T& operator*() override { return *m_Value; }

		virtual const T& operator*() const override { return *m_Value; }

		// Getters
	public:
		const bool Equal(T* obj)
		{
			return m_Value == obj;
		}

		const bool Equal(const SharedPointer& obj)
		{
			return m_Value == obj.m_Value;
		}

		template<typename OtherType>
		const bool Equal(const SharedPointer<OtherType, false>& obj)
		{
			return m_Value == obj.m_Value;
		}

		// Setters
	public:
		void SetValue(const SharedPointer& obj)
		{
			NW_ASSERT_WITHOUT_LOG(m_Value != nullptr, "This pointer already has allocated!");
			m_Value = obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
		}

		void SetValue(SharedPointer& obj)
		{
			NW_ASSERT_WITHOUT_LOG(m_Value != nullptr, "This pointer already has allocated!");
			m_Value = obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
		}

		template <typename... Types>
		void SetValue(Types... args)
		{
			NW_ASSERT_WITHOUT_LOG(m_Value == nullptr, "This pointer already has allocated!");
			m_Value = new T(std::forward<Types>(args)...);
			m_Counter = new SizeT(1);
		}
	};

	// non-nullable SharedPointer (defualt)
	template <typename T>
	class SharedPointer<T, false> : public IPointer<T>
	{
		NW_CLASS(NewWorld::DataTypes::Memory, SharedPointer<T, false>)

		// Friends
	private:
		template<typename OtherT, const bool OtherNULLABLE>
		friend class SharedPointer;

	private:
		T* m_Value = nullptr;
		uint* m_Counter = nullptr;

	public:
		SharedPointer()
		{
			m_Value = new T();
			m_Counter = new SizeT(1);
		}

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

		template<typename OtherType>
		SharedPointer(const SharedPointer<OtherType, false>& obj)
		{
			m_Value = (T*)obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
		}

		template<typename OtherType>
		SharedPointer(SharedPointer<OtherType, false>& obj)
		{
			m_Value = (T*)obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
		}

		template <typename... Types>
		SharedPointer(Types... args)
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
			m_Value = (T*)obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
			return *this;
		}
		
		template<typename OtherType>
		SharedPointer& operator= (const SharedPointer<OtherType, false>& obj)
		{
			if (m_Counter != nullptr)
			{
				this->~SharedPointer();
			}
			m_Value = (T*)obj.m_Value;
			m_Counter = obj.m_Counter;
			(*m_Counter)++;
			return *this;
		}

		virtual T* operator->() const override { return m_Value; }

		virtual T& operator*() override { return *m_Value; }

		virtual const T& operator*() const override { return *m_Value; }

		// Getters
	public:
		const bool Equal(T* obj)
		{
			return m_Value == obj;
		}

		const bool Equal(const SharedPointer& obj)
		{
			return m_Value == obj.m_Value;
		}

		template<typename OtherType>
		const bool Equal(const SharedPointer<OtherType, false>& obj)
		{
			return m_Value == obj.m_Value;
		}
	};
}