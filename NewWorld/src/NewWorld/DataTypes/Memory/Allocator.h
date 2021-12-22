#pragma once

#include "NewWorld/DataTypes/Object.h"

namespace NewWorld::DataTypes::Memory
{
	class Allocator : public Object
	{
		NW_CLASS(NewWorld::DataTypes::Memory, Allocator)

	public:
		Allocator()
		{

		}

		// Actions
	public:
		void* Allocate(Ulong size)
		{
			return std::malloc(size);
		}

		template <typename T>
		T* Allocate(Ulong length = 1)
		{
			return (T*)Allocate(length * sizeof(T));
		}

		void Deallocate(void* ptr)
		{
			std::free(ptr);
		}

		template <typename T>
		void Deallocate(T* ptr)
		{
			Deallocate((void*)ptr);
		}

		void* Reallocate(void* ptr, Ulong size)
		{
			return std::realloc(ptr, size);
		}
	};

	// Static
	Allocator s_Defualt;

	Allocator& GetActiveAllocator()
	{
		return s_Defualt;
	}
}

namespace NewWorld
{
	// Classes
	using Ulong = DataTypes::Ulong;

	// Actions
	inline void* Allocate(Ulong size)
	{
		return DataTypes::Memory::GetActiveAllocator().Allocate(size);
	}

	template <typename T>
	inline T* Allocate(Ulong length = 1)
	{
		return DataTypes::Memory::GetActiveAllocator().Allocate<T>();
	}

	inline void Deallocate(void* ptr)
	{
		return DataTypes::Memory::GetActiveAllocator().Deallocate(ptr);
	}

	template <typename T>
	inline void Deallocate(T* ptr)
	{
		return DataTypes::Memory::GetActiveAllocator().Deallocate<T>(ptr);
	}

	inline void* Reallocate(void* ptr, Ulong size)
	{
		return DataTypes::Memory::GetActiveAllocator().Reallocate(ptr, size);
	}
}

// Override
/*
void* operator new(size_t size)
{
	return NewWorld::Allocate(size);
}

void operator delete(void* ptr)
{
	NewWorld::Deallocate(ptr);
}
*/