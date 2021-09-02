#pragma once

#include "Engine/Core.h"

namespace Engine::DataTypes::Collections
{
	template <typename T, typename LENGTH_T>
	class BasicList : public Object
	{
		// Sub-Classes
		class BasicNode : public Object
		{
		public:
			T m_Value;

			BasicNode* m_PreviousNode;

			BasicNode()
				: m_PreviousNode(nullptr) {}

			BasicNode(const T& value)
				: m_Value(value), m_PreviousNode(nullptr) {}

			BasicNode(T&& value)
				: m_Value(value), m_PreviousNode(nullptr) {}

			BasicNode(const T& value, BasicNode* previousNode)
				: m_Value(value), m_PreviousNode(previousNode) {}

			BasicNode(T&& value, BasicNode* previousNode)
				: m_Value(value), m_PreviousNode(previousNode) {}
		};

		// Members
	private:
		LENGTH_T m_Length;
		BasicNode* m_TopNode;
		BasicNode* m_BottomNode;

	public:
		BasicList()
			: m_Length(0), m_TopNode(nullptr), m_BottomNode(nullptr) {}

		// Override
	public:
		virtual String ToString() const override
		{
			return String();
		}

		// Getters
		inline bool HasNodes() const
		{
			return (m_TopNode != nullptr);
		}

		inline LENGTH_T GetLength() const
		{
			return m_Length;
		}

		const T* Get(LENGTH_T index) const
		{
			if (index < m_Length)
			{
				BasicNode* node = m_TopNode;
				while (0 < index)
				{
					node = node->m_PreviousNode;
					index--;
				}
				return &(node->m_Value);
			}

			return nullptr;
		}

		T* Get(LENGTH_T index)
		{
			if (index < m_Length)
			{
				BasicNode* node = m_TopNode;
				while (0 < index)
				{
					node = node->m_PreviousNode;
					index--;
				}
				return &(node->m_Value);
			}

			return nullptr;
		}

		// Setters
		bool Set(LENGTH_T index, const T& value)
		{
			if (index < m_Length)
			{
				BasicNode* node = m_TopNode;
				while (0 < index)
				{
					node = node->m_PreviousNode;
					index--;
				}
				node->m_Value = value;
				return true;
			}
			return false;
		}

		bool Set(LENGTH_T index, T&& value)
		{
			if (index < m_Length)
			{
				BasicNode* node = m_TopNode;
				while (0 < index)
				{
					node = node->m_PreviousNode;
					index--;
				}
				node->m_Value = value;
				return true;
			}
			return false;
		}

		// Operators
		const T& operator[](LENGTH_T index) const
		{
			return *(Get(index));
		}

		T& operator[](LENGTH_T index)
		{
			return *(Get(index));
		}

		// Actions
		void Add(const T& value)
		{
			BasicNode* newNode = new BasicNode(value);

			if (HasNodes())
			{
				m_BottomNode->m_PreviousNode = newNode;
			}
			else
			{
				m_TopNode = newNode;
			}
			m_BottomNode = newNode;

			m_Length++;
		}

		void Add(T&& value)
		{
			BasicNode* newNode = new BasicNode(value);

			if (HasNodes())
			{
				m_BottomNode->m_PreviousNode = newNode;
			}
			else
			{
				m_TopNode = newNode;
			}
			m_BottomNode = newNode;

			m_Length++;
		}

		bool Add(LENGTH_T index, const T& value)
		{
			if (index < m_Length)
			{
				if (index == 0)
				{
					BasicNode* newNode = new BasicNode(value, m_TopNode);
					m_TopNode = newNode;
				}
				else
				{
					BasicNode* node = m_TopNode;
					while (1 < index)
					{
						node = node->m_PreviousNode;
						index--;
					}
					BasicNode* newNode = new BasicNode(value, node->m_PreviousNode);
					node->m_PreviousNode = newNode;
				}
				m_Length++;

				return true;
			}
			else if (index == m_Length)
			{
				Add(value);
				return true;
			}

			return false;
		}

		bool Add(LENGTH_T index, T&& value)
		{
			if (index < m_Length)
			{
				if (index == 0)
				{
					BasicNode* newNode = new BasicNode(value, m_TopNode);
					m_TopNode = newNode;
				}
				else
				{
					BasicNode* node = m_TopNode;
					while (1 < index)
					{
						node = node->m_PreviousNode;
						index--;
					}
					BasicNode* newNode = new BasicNode(value, node->m_PreviousNode);
					node->m_PreviousNode = newNode;
				}
				m_Length++;

				return true;
			}
			else if (index == m_Length)
			{
				Add(value);
				return true;
			}

			return false;
		}

		bool Remove(LENGTH_T index)
		{
			if (index < m_Length)
			{
				BasicNode* node = m_TopNode;
				if (index == 0)
				{
					m_TopNode = m_TopNode->m_PreviousNode;
				}
				else
				{
					while (1 < index)
					{
						node = node->m_PreviousNode;
						index--;
					}

					BasicNode* nodeBefore = node;
					node = node->m_PreviousNode;
					
					BasicNode* nodeAfter = node->m_PreviousNode;
					if (nodeAfter != nullptr)
					{
						nodeBefore->m_PreviousNode = nodeAfter;
					}
					else
					{
						m_BottomNode = nodeBefore;
					}
				}

				delete node;
				m_Length--;

				return true;
			}

			return false;
		}

		bool Remove(LENGTH_T index, LENGTH_T count)
		{
			if (index + count - 1 < m_Length)
			{
				if (count == m_Length)
				{
					Clear();
				}
				else
				{
					m_Length -= count;

					BasicNode* firstNode;
					BasicNode* node;
					if (index == 0)
					{
						firstNode = nullptr;
						node = m_TopNode;
					}
					else
					{
						firstNode = m_TopNode;
						while (1 < index)
						{
							firstNode = firstNode->m_PreviousNode;
							index--;
						}

						node = firstNode->m_PreviousNode;
					}

					while (0 < count)
					{
						BasicNode* nextNode = node->m_PreviousNode;
						delete node;
						node = nextNode;
						count--;
					}

					if (firstNode == nullptr)
					{
						m_TopNode = node;
					}
					else
					{
						firstNode->m_PreviousNode = node;
					}

					if (node == nullptr)
					{
						m_BottomNode = firstNode;
					}
				}

				return true;
			}

			return false;
		}

		void Clear()
		{
			BasicNode* node = m_TopNode;
			while (node != nullptr)
			{
				BasicNode* nextNode = node->m_PreviousNode;
				delete node;
				node = nextNode;
			}

			m_TopNode = nullptr;
			m_BottomNode = nullptr;
			m_Length = 0;
		}
	};
}