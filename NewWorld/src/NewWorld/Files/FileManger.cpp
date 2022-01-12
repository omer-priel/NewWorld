#include "nwpch.h"
#include "FileManger.h"

namespace NewWorld::Files
{
	String FileManger::s_RootDirectory = "";
	uint FileManger::s_LastTemporaryDirectoryID = 0;
}