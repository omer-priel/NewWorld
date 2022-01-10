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
		static String s_RootDirectory;

		// Init
	public:
		static void Initialize()
		{
			String buffer(MAX_PATH);
			GetModuleFileNameA(NULL, (char*)buffer.GetPointer(), MAX_PATH);
			s_RootDirectory = buffer.Substring(0, buffer.FindLast('\\')+1);
		}

		// Getters
	public:
		static const String GetRootDirectory(String subPath = "")
		{
			return s_RootDirectory + subPath;
		}

		// String GetLogsDirectory()
		// String GetTemporaryDirectory(uint& outId)
		// String GetTemporaryDirectory(uint id)
	};

	String FileManger::s_RootDirectory = "";
}