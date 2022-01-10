#pragma once

#include "NewWorld/Minimal.h"

#include <filesystem>

namespace NewWorld::Files
{
	class Directory : public Object
	{
	NW_CLASS(NewWorld::Files, Directory)

		// Static Functions
	public:
		static inline bool Exists(const String& path)
		{
			return std::filesystem::is_directory(path.GetPointer());
		}

		static inline bool Create(const String& path)
		{
			return std::filesystem::create_directory(path.GetPointer());
		}
	};
}
