#pragma once

#include "NewWorld/DataTypes/Memory/IPointer.h"

namespace NewWorld::DataTypes::Memory
{
	template <typename T>
	class ScopePointer : public IPointer
	{
	NW_CLASS(ScopePointer, NewWorld::DataTypes::Memory)

	private:
		T* m_Value;

	public:
		ScopePointer()
			: m_Value(nullptr)
		{

		}

		ScopePointer(const T& value)
			: m_Value(value)
		{

		}

		ScopePointer(T&& value)
			: m_Value(value)
		{

		}

		~ScopePointer()
		{
			if (m_Value != nullptr)
			{
				delete m_Value;
			}
		}
	};
}