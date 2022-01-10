#pragma once

#include "NewWorld/Minimal.h"

#include <filesystem>

namespace NewWorld::Files
{
	class File : public Object
	{
	NW_CLASS(NewWorld::Files, File)

		// Static Functions
	public:
		static inline bool Exists(const String& path)
		{
			std::error_code errorCode;
			return (std::filesystem::status(path.GetPointer(), errorCode).type()) == std::filesystem::file_type::regular;
		}

		// Members
	private:

		// Actions
	public:

		// Read
	public:

		// Write
	public:

	};
}