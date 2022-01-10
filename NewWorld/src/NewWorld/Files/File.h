#pragma once

#include "NewWorld/Minimal.h"

#include <filesystem>
#include <fstream>

namespace NewWorld::Files
{
	class File : public Object
	{
	NW_CLASS(NewWorld::Files, File)

		// Static Functions
	public:
		static inline bool Exists(const String& path)
		{
			return std::filesystem::is_regular_file(path.GetPointer());
		}

		// Members
	private:
		std::fstream m_Stream;
		const String& m_Path;

	public:
		File(const String& path)
			: m_Path(path)
		{

		}

		File(const String& path)
			: m_Path(path)
		{

		}

		// Actions
	public:

		// Read
	public:

		// Write
	public:

	};
}