#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Files/File.h"

namespace NewWorld::Files
{
	class BinaryFile : public File
	{
	NW_CLASS(NewWorld::Files, BinaryFile)

	public:
		BinaryFile(const String& path, bool create = false, bool readOnly = false)
			: File(path, create, false, readOnly)
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