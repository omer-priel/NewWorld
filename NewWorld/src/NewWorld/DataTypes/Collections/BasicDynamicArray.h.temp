#pragma once

// TODO Remove this
#include <utility>

#include "Engine/Core.h"

namespace Engine::DataTypes::Collections
{
	template <typename T, typename LENGTH_T, const LENGTH_T CHANK_SIZE>
	class BasicDynamicArray : public Object
	{
		// Members
	private:
		T* m_Elements = nullptr;

		LENGTH_T m_Length = 0;
		LENGTH_T m_Capacity = 0;

		// Constructors
	public:
		BasicDynamicArray()
		{

		}

		BasicDynamicArray(LENGTH_T capacity)
		{
			Reallocate(capacity);
		}

		// Destructor
		~BasicDynamicArray()
		{
			Clear();
			delete[] m_Elements;
		}

		// Override
	public:
		virtual String ToString() const override
		{
			return String();
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
			// TODO Check if the index is bigger than length (in DEBUG CONFIG)
			return m_Elements[index];
		}

		// Setters
		void Set(LENGTH_T index, const T& value)
		{
			// TODO Check if the index is bigger than length (in DEBUG CONFIG)
			m_Elements[index] = value;
		}

		void Set(LENGTH_T index, T&& value)
		{
			// TODO Check if the index is bigger than length (in DEBUG CONFIG)
			m_Elements[index] = std::move(value);
		}

		// Operators
		const T& operator[](LENGTH_T index) const
		{
			// TODO Check if the index is bigger than length (in DEBUG CONFIG)
			return m_Elements[index];
		}

		T& operator[](LENGTH_T index)
		{
			// TODO Check if the index is bigger than length (in DEBUG CONFIG)
			return m_Elements[index];
		}

		// Actions
		void Push(const T& value)
		{
			if (m_Length >= m_Capacity)
			{
				Reallocate(m_Capacity + CHANK_SIZE);
			}

			m_Elements[m_Length] = value;
			m_Length++;
		}

		void Push(T&& value)
		{
			if (m_Length >= m_Capacity)
			{
				Reallocate(m_Capacity + CHANK_SIZE);
			}

			m_Elements[m_Length] = std::move(value);
			m_Length++;
		}

		template <typename... Args>
		T& Emplace(Args&&... args)
		{
			if (m_Length >= m_Capacity)
			{
				Reallocate(m_Capacity + CHANK_SIZE);
			}

			new(&m_Elements[m_Length]) T(std::forward<Args>(args)...);
			m_Length++;

			return m_Elements[m_Length];
		}

	public:
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
			T* newBlock = new T[newCapacity];

			// TODO Check if the newCapacity is smaller than the Capacity 
			for (LENGTH_T i = 0; i < m_Length; i++)
			{
				newBlock[i] = std::move(m_Elements[i]);
			}

			delete[] m_Elements;
			m_Elements = newBlock;
			m_Capacity = newCapacity;
		}
	};
}