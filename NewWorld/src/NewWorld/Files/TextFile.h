#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Files/File.h"

namespace NewWorld::Files
{
	class TextFile : public File
	{
	NW_CLASS(NewWorld::Files, TextFile)

	public:
		TextFile(const String& path, bool create = false, bool readOnly = false)
			: File(path, create, true, readOnly)
		{

		}

		// Open
	public:

		// Read
	public:

		// Write
	public:

	};
}