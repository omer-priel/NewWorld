#pragma once

#include "NewWorld/DataTypes/Object.h"

namespace NewWorld::DataTypes::Memory
{
	class Allocator : public Object
	{
		NW_CLASS(Allocator, NewWorld::DataTypes::Memory)

	public:
		Allocator()
		{

		}

		// Actions
	public:
		void* Allocate(uint size)
		{
			return std::malloc(size);
		}

		template <typename T>
		T* Allocate()
		{
			return (T*)Allocate(sizeof(T));
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

		void* Reallocate(void* ptr, uint size)
		{
			return std::realloc(ptr, size);
		}

		template <typename T>
		T* Reallocate(void* ptr)
		{
			return (T*)Reallocate(ptr, sizeof(T));
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
	using uint = DataTypes::uint;

	inline void* Allocate(uint size)
	{
		return DataTypes::Memory::GetActiveAllocator().Allocate(size);
	}

	template <typename T>
	inline T* Allocate()
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

	inline void* Reallocate(void* ptr, uint size)
	{
		return DataTypes::Memory::GetActiveAllocator().Reallocate(ptr, size);
	}

	template <typename T>
	inline T* Reallocate(void* ptr)
	{
		return DataTypes::Memory::GetActiveAllocator().Reallocate<T>(ptr);
	}
}
