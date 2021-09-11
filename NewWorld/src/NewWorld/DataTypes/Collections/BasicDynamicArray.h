#pragma once

#include "NewWorld/DataTypes/Object.h"

#include "Dependencies.h"

namespace NewWorld::DataTypes::Collections
{
	template <typename T, typename LENGTH_T, const LENGTH_T CHANK_SIZE>
	class BasicDynamicArray : public Object
	{
	NW_CLASS(BasicDynamicArray, NewWorld::DataTypes::Collections)

			// Members
	private:
		T* m_Elements;

		LENGTH_T m_Length;
		LENGTH_T m_Capacity;

		// Constructors
	public:
		BasicDynamicArray()
			: m_Elements(nullptr), m_Length(0), m_Capacity(0)
		{

		}

		BasicDynamicArray(LENGTH_T capacity)
			: m_Elements(nullptr), m_Length(0), m_Capacity(0)
		{
			Reallocate(capacity);
		}

		// Destructor
		~BasicDynamicArray()
		{
			Clear();
			delete[] m_Elements;
		}

		// Getters
	public:
		inline LENGTH_T GetLength() const
		{
			return m_Length;
		}

		inline LENGTH_T GetCapacity() const
		{
			return m_Capacity;
		}

		const T* Get() const
		{
			return m_Elements;
		}

		T* Get()
		{
			return m_Elements;
		}

		const T& Get(LENGTH_T index) const
		{
			NW_ASSERT(index >= m_Length, "Index cannot be bigger than the Length!")
			return m_Elements[index];
		}

		// Setters
	public:
		void SetCapacity(LENGTH_T capacity)
		{
			if (capacity > m_Length)
			{
				Reallocate(capacity);
			}
		}
		
		void Set(LENGTH_T index, const T& value)
		{
			NW_ASSERT(index < m_Length, "Index cannot be bigger than the Length!")
			m_Elements[index] = value;
		}

		void Set(LENGTH_T index, T&& value)
		{
			NW_ASSERT(index < m_Length, "Index cannot be bigger than the Length!")
			m_Elements[index] = std::move(value);
		}

		// Operators
	public:
		const T& operator[](LENGTH_T index) const
		{
			NW_ASSERT(index < m_Length, "Index cannot be bigger than the Length!")
			return m_Elements[index];
		}

		T& operator[](LENGTH_T index)
		{
			NW_ASSERT(index < m_Length, "Index cannot be bigger than the Length!")
			return m_Elements[index];
		}

		// Actions
	public:
		void Push(const T& value)
		{
			if (m_Length >= m_Capacity)
			{
				Reallocate(m_Capacity + CHANK_SIZE);
			}

			new(&m_Elements[m_Length]) T(value);
			m_Length++;
		}

		void Push(T&& value)
		{
			if (m_Length >= m_Capacity)
			{
				Reallocate(m_Capacity + CHANK_SIZE);
			}

			new(&m_Elements[m_Length]) T(value);
			m_Length++;
		}

		template <typename... Types>
		T& Emplace(Types&&... args)
		{
			if (m_Length >= m_Capacity)
			{
				Reallocate(m_Capacity + CHANK_SIZE);
			}

			new(&m_Elements[m_Length]) T(std::forward<Types>(args)...);
			m_Length++;

			return m_Elements[m_Length - 1];
		}

		void Clear()
		{
			for (LENGTH_T i = 0; i < m_Length; i++)
			{
				m_Elements[i].~T();
			}

			m_Length = 0;
		}

	private:
		void Reallocate(LENGTH_T newCapacity)
		{
			m_Elements = (T*)std::realloc(m_Elements, newCapacity * sizeof(T));
			m_Capacity = newCapacity;
		}
	};
}