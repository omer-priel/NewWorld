#include "nwpch.h"
#include "FileManager.h"

namespace NewWorld::Files
{
	String FileManager::s_RootDirectory = "";
	uint FileManager::s_LastTemporaryDirectoryID = 0;
}