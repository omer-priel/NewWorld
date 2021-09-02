#pragma once

#include "NewWorld/DataTypes/Memory/IPointer.h"

namespace NewWorld::DataTypes::Memory
{
	template <typename T>
	class SharedPointer : public IPointer
	{
	NW_CLASS(SharedPointer, NewWorld::DataTypes::Memory)


	};
}