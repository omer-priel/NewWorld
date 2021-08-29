#pragma once

#include "Engine/Core.h"

namespace Engine::DataTypes::Collections
{
	template <typename T>
	class BasicDeque : public Object
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
		BasicNode* m_TopNode;
		BasicNode* m_BottomNode;

	public:
		BasicDeque()
			: m_TopNode(nullptr), m_BottomNode(nullptr) {}

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

		const T* GetTop() const
		{
			if (HasNodes())
			{
				return &(m_TopNode->m_Value);
			}

			return nullptr;
		}

		T* GetTop()
		{
			if (HasNodes())
			{
				return &(m_TopNode->m_Value);
			}

			return nullptr;
		}

		const T* GetBottom() const
		{
			if (HasNodes())
			{
				return &(m_BottomNode->m_Value);
			}

			return nullptr;
		}

		T* GetBottom()
		{
			if (HasNodes())
			{
				return &(m_BottomNode->m_Value);
			}

			return nullptr;
		}

		// Actions
		void PushToTop(const T& value)
		{
			BasicNode* newNode;
			if (HasNodes())
			{
				newNode = new BasicNode(value, m_TopNode);
			}
			else
			{
				newNode = new BasicNode(value);
				m_BottomNode = newNode;
			}

			m_TopNode = newNode;
		}

		void PushToTop(T&& value)
		{
			BasicNode* newNode;
			if (HasNodes())
			{
				newNode = new BasicNode(value, m_TopNode);
			}
			else
			{
				newNode = new BasicNode(value);
				m_BottomNode = newNode;
			}

			m_TopNode = newNode;
		}

		void PushToBottom(const T& value)
		{
			BasicNode* newNode;
			if (HasNodes())
			{
				newNode = new BasicNode(value, nullptr, m_BottomNode);
			}
			else
			{
				newNode = new BasicNode(value);
				m_TopNode = newNode;
			}

			m_BottomNode = newNode;
		}

		void PushToBottom(T&& value)
		{
			BasicNode* newNode;
			if (HasNodes())
			{
				newNode = new BasicNode(value, nullptr, m_BottomNode);
			}
			else
			{
				newNode = new BasicNode(value);
				m_TopNode = newNode;
			}

			m_BottomNode = newNode;
		}

		T PullFromTop()
		{
			if (HasNodes())
			{
				BasicNode* node = m_TopNode;
				m_TopNode = m_TopNode->m_PreviousNode;
				if (m_TopNode == nullptr)
				{
					m_BottomNode = nullptr;
				}
				else
				{
					m_TopNode->m_NextNode = nullptr;
				}

				return node->m_Value;
			}

			return {};
		}

		T PullFromBottom()
		{
			if (HasNodes())
			{
				BasicNode* node = m_BottomNode;
				m_BottomNode = m_BottomNode->m_NextNode;
				if (m_BottomNode == nullptr)
				{
					m_TopNode = nullptr;
				}
				else
				{
					m_BottomNode->m_PreviousNode = nullptr;
				}

				return node->m_Value;
			}

			return {};
		}
	};
}