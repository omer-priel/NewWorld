#pragma once

#include <utility>

#include "NewWorld/DataTypes/Object.h"

namespace NewWorld::DataTypes::Collections
{
	template <typename T, typename LENGTH_T, const LENGTH_T LENGTH>
	class BasicArray : public Object
	{
	NW_CLASS(BasicArray, NewWorld::DataTypes::Collections)

		// Members
	private:
		T m_Elements[LENGTH];

		// Constructors
	public:
		BasicArray()
		{
			
		}

		// Getters
	public:
		constexpr LENGTH_T GetLength() const
		{
			return LENGTH;
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
			NW_ASSERT(index < LENGTH, "Index cannot be bigger than the Length!")
			return m_Elements[index];
		}

		// Setters
	public:
		void Set(LENGTH_T index, const T& value)
		{
			NW_ASSERT(index < LENGTH, "Index cannot be bigger than the Length!")
			m_Elements[index] = value;
		}

		void Set(LENGTH_T index, T&& value)
		{
			NW_ASSERT(index < LENGTH, "Index cannot be bigger than the Length!")
			m_Elements[index] = std::move(value);
		}

		// Operators
	public:
		const T& operator[](LENGTH_T index) const
		{
			NW_ASSERT(index < LENGTH, "Index cannot be bigger than the Length!")
			return m_Elements[index];
		}

		T& operator[](LENGTH_T index)
		{
			NW_ASSERT(index < LENGTH, "Index cannot be bigger than the Length!")
			return m_Elements[index];
		}

		// Actions
	public:
		void Fill(const T& value)
		{
			for (LENGTH_T i = 0; i < LENGTH; i++)
			{
				m_Elements[i] = value;
			}
		}

		void Fill(T&& value)
		{
			for (LENGTH_T i = 0; i < LENGTH; i++)
			{
				m_Elements[i] = std::move(value);
			}
		}

		template <typename... Types>
		void Fill(Types&&... args)
		{
			for (LENGTH_T i = 0; i < LENGTH; i++)
			{
				m_Elements[i] = T(std::forward<Types>(args)...);
			}
		}
	};
}