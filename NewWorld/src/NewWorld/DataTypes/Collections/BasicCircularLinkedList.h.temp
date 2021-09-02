#pragma once

#include "Engine/Core.h"

namespace Engine::DataTypes::Collections
{
	template <typename T, typename LENGTH_T>
	class BasicCircularLinkedList : public Object
	{
		// Sub-Classes
		class BasicNode : public Object
		{
		public:
			T m_Value;

			BasicNode* m_PreviousNode;
			BasicNode* m_NextNode;

			BasicNode()
				: m_PreviousNode(nullptr), m_NextNode(nullptr) {}

			BasicNode(const T& value)
				: m_Value(value), m_PreviousNode(nullptr), m_NextNode(nullptr) {}

			BasicNode(T&& value)
				: m_Value(value), m_PreviousNode(nullptr), m_NextNode(nullptr) {}

			BasicNode(const T& value, BasicNode* previousNode)
				: m_Value(value), m_PreviousNode(previousNode), m_NextNode(nullptr) {}

			BasicNode(T&& value, BasicNode* previousNode)
				: m_Value(value), m_PreviousNode(previousNode), m_NextNode(nullptr) {}

			BasicNode(const T& value, BasicNode* previousNode, BasicNode* nextNode)
				: m_Value(value), m_PreviousNode(previousNode), m_NextNode(nextNode) {}

			BasicNode(T&& value, BasicNode* previousNode, BasicNode* nextNode)
				: m_Value(value), m_PreviousNode(previousNode), m_NextNode(nextNode) {}
		};

		// Members
	private:
		LENGTH_T m_Length;

		BasicNode* m_CurrentNode;

	public:
		BasicCircularLinkedList()
			: m_Length(0), m_CurrentNode(nullptr) {}

		// Override
	public:
		virtual String ToString() const override
		{
			return String();
		}

		// Getters
		inline bool HasNodes() const
		{
			return (m_CurrentNode != nullptr);
		}

		inline LENGTH_T GetLength() const
		{
			return m_Length;
		}

		const T* Get() const
		{
			if (HasNodes())
			{
				return &(m_CurrentNode->m_Value);
			}

			return nullptr;
		}

		T* Get()
		{
			if (HasNodes())
			{
				return &(m_CurrentNode->m_Value);
			}

			return nullptr;
		}

		// Setters
		void Set(const T& value)
		{
			if (HasNodes())
			{
				m_CurrentNode->m_Value = value;
			}
			else
			{
				Push(value);
			}
		}

		void Set(T&& value)
		{
			if (HasNodes())
			{
				m_CurrentNode->m_Value = value;
			}
			else
			{
				Push(value);
			}
		}

		// Operators
		T* operator++()
		{
			if (HasNodes())
			{
				m_CurrentNode = m_CurrentNode->m_PreviousNode;

				return &(m_CurrentNode->m_Value);
			}
			return nullptr;
		}

		T* operator++(int)
		{
			if (HasNodes())
			{
				m_CurrentNode = m_CurrentNode->m_PreviousNode;

				return &(m_CurrentNode->m_Value);
			}
			return nullptr;
		}

		T* operator--()
		{
			if (HasNodes())
			{
				m_CurrentNode = m_CurrentNode->m_NextNode;

				return &(m_CurrentNode->m_Value);
			}
			return nullptr;
		}

		T* operator--(int)
		{
			if (HasNodes())
			{
				m_CurrentNode = m_CurrentNode->m_NextNode;

				return &(m_CurrentNode->m_Value);
			}
			return nullptr;
		}

		T* operator+=(const LENGTH_T& count)
		{
			if (HasNodes())
			{
				count %= m_Length;
				while (count > 0)
				{
					m_CurrentNode = m_CurrentNode->m_PreviousNode;
					count--;
				}

				return &(m_CurrentNode->m_Value);
			}
			return nullptr;
		}

		T* operator+=(LENGTH_T&& count)
		{
			if (HasNodes())
			{
				count %= m_Length;
				while (count > 0)
				{
					m_CurrentNode = m_CurrentNode->m_PreviousNode;
					count--;
				}

				return &(m_CurrentNode->m_Value);
			}
			return nullptr;
		}

		T* operator-=(const LENGTH_T& count)
		{
			if (HasNodes())
			{
				count %= m_Length;
				while (count > 0)
				{
					m_CurrentNode = m_CurrentNode->m_NextNode;
					count--;
				}

				return &(m_CurrentNode->m_Value);
			}
			return nullptr;
		}

		T* operator-=(LENGTH_T&& count)
		{
			if (HasNodes())
			{
				count %= m_Length;
				while (count > 0)
				{
					m_CurrentNode = m_CurrentNode->m_NextNode;
					count--;
				}

				return &(m_CurrentNode->m_Value);
			}
			return nullptr;
		}

		// Actions
		void Push(const T& value)
		{
			BasicNode* newNode;
			
			if (HasNodes())
			{
				newNode = new BasicNode(value, m_CurrentNode, m_CurrentNode->m_NextNode);
				
				(m_CurrentNode->m_NextNode)->m_PreviousNode = newNode;
				m_CurrentNode->m_NextNode = newNode;
				
			}
			else
			{
				newNode = new BasicNode(value);

				newNode->m_PreviousNode = newNode;
				newNode->m_NextNode = newNode;
			}

			m_CurrentNode = newNode;
			m_Length++;
		}

		void Push(T&& value)
		{
			BasicNode* newNode;

			if (HasNodes())
			{
				newNode = new BasicNode(value, m_CurrentNode, m_CurrentNode->m_NextNode);

				(m_CurrentNode->m_NextNode)->m_PreviousNode = newNode;
				m_CurrentNode->m_NextNode = newNode;

			}
			else
			{
				newNode = new BasicNode(value);

				newNode->m_PreviousNode = newNode;
				newNode->m_NextNode = newNode;
			}

			m_CurrentNode = newNode;
			m_Length++;
		}

		T Pull()
		{
			if (HasNodes())
			{
				BasicNode* node = m_CurrentNode;
				if (m_Length == 1)
				{
					m_CurrentNode = nullptr;
				}
				else
				{
					(m_CurrentNode->m_PreviousNode)->m_NextNode = m_CurrentNode->m_NextNode;
					(m_CurrentNode->m_NextNode)->m_PreviousNode = m_CurrentNode->m_PreviousNode;

					m_CurrentNode = m_CurrentNode->m_PreviousNode;
				}

				m_Length--;

				return node->m_Value;
			}

			return {};
		}
	};
}