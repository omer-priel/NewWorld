#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Files/Directory.h"
#include "NewWorld/Files/File.h"

namespace NewWorld::Files
{
	// This is static class
	class FileManger : public Object
	{
	NW_CLASS(NewWorld::Files, FileManger)

		// Members
	private:
		static String s_RootDirectory;
		static uint s_LastTemporaryDirectoryID;

		// Init
	public:
		static void Initialize()
		{
			String buffer(MAX_PATH);
			GetModuleFileNameA(NULL, (char*)buffer.GetPointer(), MAX_PATH);
			s_RootDirectory = Directory::GetDirectoryOfFile(buffer);

			// Temporary Directory
			Directory::Delete(GetRootDirectory("temp"));
		}

		// Getters
	public:
		static inline bool Exists(const String& path)
		{
			return std::filesystem::exists(path.GetPointer());
		}

		static String GetRootDirectory(const String& subPath = "")
		{
			return s_RootDirectory + subPath;
		}

		static String GetLogsDirectory(const String& subPath = "")
		{
			return GetRootDirectory("logs\\" + subPath);
		}

		static String GetAssetPath(const String& asset = "")
		{
			String path = GetRootDirectory("assets\\" + asset);
			path.Replace('/', '\\');
			return path;
		}

		static uint CreateTemporaryDirectory()
		{
			uint id = s_LastTemporaryDirectoryID;
			s_LastTemporaryDirectoryID++;

			Directory::Create(GetTemporaryDirectory((uint)id));
			
			return id;
		}

		static String GetTemporaryDirectory(uint id, const String& subPath = "")
		{
			return String::Format("{}temp\\{}\\{}", GetRootDirectory(), id, subPath);
		}
	};
}