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
			return std::filesystem::is_directory(path.GetPointer());
		}

		// Create Only the last directory
		static inline bool CreateSingle(const String& path)
		{
			return std::filesystem::create_directory(path.GetPointer());
		}
		
		// Create Full Directory path
		static inline bool Create(const String& path)
		{
			return std::filesystem::create_directories(path.GetPointer());
		}

		static bool Delete(const String& path)
		{
			if (Exists(path)) {
				return std::filesystem::remove_all(path.GetPointer());
			}
			return true;
		}

		static String GetDirectoryOfFile(const String& path)
		{
			return path.Substring(0, path.FindLast('\\') + 1);
		}

		// Get Directory Entities
		static void GetDirectories(const String& path, DynamicArray<String>& output)
		{
			for (const auto& entry : std::filesystem::directory_iterator(path.GetPointer()))
			{
				if (entry.is_directory())
				{
					output.push_back(String(entry.path().string().c_str()));
				}
			}
		}

		static void GetDirectoriesNames(const String& path, DynamicArray<String>& output)
		{
			for (const auto& entry : std::filesystem::directory_iterator(path.GetPointer()))
			{
				if (entry.is_directory())
				{
					output.push_back(String(entry.path().filename().string().c_str()));
				}
			}
		}

		static void GetFiles(const String& path, DynamicArray<String>& output)
		{
			for (const auto& entry : std::filesystem::directory_iterator(path.GetPointer()))
			{
				if (entry.is_regular_file())
				{
					output.push_back(String(entry.path().string().c_str()));
				}
			}
		}

		static void GetFilesNames(const String& path, DynamicArray<String>& output)
		{
			for (const auto& entry : std::filesystem::directory_iterator(path.GetPointer()))
			{
				if (entry.is_regular_file())
				{
					output.push_back(String(entry.path().filename().string().c_str()));
				}
			}
		}

		static void GetDirectoriesAndFiles(const String& path, DynamicArray<String>& output)
		{
			for (const auto& entry : std::filesystem::directory_iterator(path.GetPointer()))
			{
				if (entry.is_directory() || entry.is_regular_file())
				{
					output.push_back(String(entry.path().string().c_str()));
				}
			}
		}

		static void GetDirectoriesAndFilesNames(const String& path, DynamicArray<String>& output)
		{
			for (const auto& entry : std::filesystem::directory_iterator(path.GetPointer()))
			{
				if (entry.is_directory() || entry.is_regular_file())
				{
					output.push_back(String(entry.path().filename().string().c_str()));
				}
			}
		}
	};
}
