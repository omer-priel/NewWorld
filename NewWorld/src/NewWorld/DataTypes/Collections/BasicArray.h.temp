#pragma once

// TODO Remove this
#include <utility>

#include "Engine/Core.h"

namespace Engine::DataTypes::Collections
{
	template <typename T, typename LENGTH_T, const LENGTH_T LENGTH>
	class BasicArray : public Object
	{
		// Members
	private:
		T m_Elements[LENGTH];

	public:
		BasicArray()
		{

		}

		// Override
	public:
		virtual String ToString() const override
		{
			if (LENGTH == 0)
			{
				// TODO return String("{}");
				return String();
			}

			// TODO Replace with stream string
			String text; // = "{ "
			for (LENGTH_T i = 0; i < LENGTH - 1; i++)
			{
				const T& item = m_Elements[i];
				// text += Object::ToString(item) + ", ";
			}

			// text += Object::ToString(m_Elements[LENGTH - 1]) + "}";
			return text;
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
	};
}