#pragma once

#include "Engine/Core.h"

#include "Engine/DataTypes/Collections/BasicBinaryTree.h"

namespace Engine::DataTypes::Collections
{
	template <typename T>
	class BasicBinarySearchTree : public BasicBinaryTree<T>
	{
		// Sub-Classes
		using BasicNode = BasicBinaryTree<T>::BasicNode;

		// Members
	private:
		BasicNode* m_TopNode;

		// Actions
		void Push(const T& value);
		void Push(T&& value);
	};
}