#pragma once

#include "Engine/Core.h"

namespace Engine::DataTypes::Collections
{
	template <typename T>
	class BasicBinaryTree : public Object
	{
		// Sub-Classes
		class BasicNode : public Object
		{
		public:
			T m_Value;

			BasicNode* m_Parent;
			BasicNode* m_Left;
			BasicNode* m_Right;

			BasicNode()
				: m_Parent(nullptr), m_Left(nullptr), m_Right(nullptr) {}

			BasicNode(const T& value)
				: m_Value(value), m_Parent(nullptr), m_Left(nullptr), m_Right(nullptr) {}

			BasicNode(T&& value)
				: m_Value(value), m_Parent(nullptr), m_Left(nullptr), m_Right(nullptr) {}

			BasicNode(const T& value, BasicNode* parent)
				: m_Value(value), m_Parent(parent), m_Left(nullptr), m_Right(nullptr) {}

			BasicNode(T&& value, BasicNode* parent)
				: m_Value(value), m_Parent(parent), m_Left(nullptr), m_Right(nullptr) {}

			BasicNode(const T& value, BasicNode* parent, BasicNode* left, BasicNode* right)
				: m_Value(value), m_Parent(parent), m_Left(left), m_Right(right) {}

			BasicNode(T&& value, BasicNode* parent, BasicNode* left, BasicNode* right)
				: m_Value(value), m_Parent(parent), m_Left(left), m_Right(right) {}
		};

		// Members
	private:
		BasicNode* m_TopNode;

	public:
		BasicBinaryTree()
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
	};
}