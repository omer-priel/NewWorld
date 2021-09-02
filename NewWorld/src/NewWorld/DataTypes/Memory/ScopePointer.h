#pragma once

#include "NewWorld/DataTypes/Memory/IPointer.h"

namespace NewWorld::DataTypes::Memory
{
	template <typename T>
	class ScopePointer : public IPointer
	{
	NW_CLASS(ScopePointer, NewWorld::DataTypes::Memory)


	};
}