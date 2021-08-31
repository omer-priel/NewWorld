#pragma once

#include "Engine/Core.h"

namespace Engine::DataTypes::Collections
{
	template <typename T>
	class BasicStack : public Object
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
		BasicNode* m_TopNode;

	public:
		BasicStack()
			: m_TopNode(nullptr) {}

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

		const T* Get() const
		{
			if (HasNodes())
			{
				return &(m_TopNode->m_Value);
			}

			return nullptr;
		}

		T* Get()
		{
			if (HasNodes())
			{
				return &(m_TopNode->m_Value);
			}

			return nullptr;
		}

		// Actions
		void Push(const T& value)
		{
			BasicNode* newNode;
			if (HasNodes())
			{
				newNode = new BasicNode(value, m_TopNode);
			}
			else
			{
				newNode = new BasicNode(value);
			}

			m_TopNode = newNode;
		}

		void Push(T&& value)
		{
			BasicNode* newNode;
			if (HasNodes())
			{
				newNode = new BasicNode(value, m_TopNode);
			}
			else
			{
				newNode = new BasicNode(value);
			}

			m_TopNode = newNode;
		}

		T Pull()
		{
			if (HasNodes())
			{
				BasicNode* node = m_TopNode;
				m_TopNode = m_TopNode->m_PreviousNode;
				return node->m_Value;
			}

			return {};
		}
	};
}