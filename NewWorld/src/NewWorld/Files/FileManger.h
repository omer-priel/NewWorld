#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Files/File.h"
#include "NewWorld/Files/Directory.h"

namespace NewWorld::Files
{
	// This is static class
	class FileManger : public Object
	{
	NW_CLASS(NewWorld::Files, FileManger)

			// Members
	private:
		static String m_RootDirectory;

		// Setters
	public:
		// void SetRootDirectory(String path)

		// Getters
	public:
		// String GetRootDirectory(String subPath)
		// String GetLogsDirectory()
		// String GetTemporaryDirectory(uint& outId)
		// String GetTemporaryDirectory(uint id)
	};
}