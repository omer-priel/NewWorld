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
			std::error_code errorCode;
			return (std::filesystem::status(path.GetPointer(), errorCode).type()) == std::filesystem::file_type::directory;
		}
	};
}
