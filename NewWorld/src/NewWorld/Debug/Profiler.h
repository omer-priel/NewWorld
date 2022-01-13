#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Debug
{
	// This is Static class
	class Profiler : public Object
	{
	NW_CLASS(NewWorld::Debug, Profiler)

		// Members
	public:
		static Files::TextFile s_File;
		static bool s_IsFirstEvent;

		// Actions
	public:
		static void Initialize()
		{
			s_IsFirstEvent = true;

			String path = Files::FileManger::GetRootDirectory("profile.json");

			Files::File::Delete(path);
			s_File.Open(path, true);

			s_File << "{\"displayTimeUnit\":\"ms\",";
			s_File << "\"otherData\": {},\"traceEvents\":[";
		}

		static void Finalize()
		{
			s_File << "]}";
			s_File.Close();
		}

		static void AddEvent(String name)
		{
			uint threadID = 0;
			if (s_IsFirstEvent)
			{
				s_IsFirstEvent = false;
			}
			else
			{
				s_File << ",";
			}

			name.Replace('"', '\'');

			s_File << "{";
			s_File << String::Format("\"name\":\"{}\",", name);
			s_File << "\"cat\":\"Event\",";
			s_File << "\"ph\":\"X\",";
			s_File << String::Format("\"dur\":50,\"ts\":{},", Time::Now().GetTicks());
			s_File << String::Format("\"pid\":0,\"tid\":{}", threadID);
			s_File << "}";
		}

		static void AddBlock(String name, Ulong start, Ulong end)
		{
			uint threadID = 0;
			if (s_IsFirstEvent)
			{
				s_IsFirstEvent = false;
			}
			else
			{
				s_File << ",";
			}

			name.Replace('"', '\'');

			s_File << "{";
			s_File << String::Format("\"name\":\"{}\",", name);
			s_File << "\"cat\":\"Block\",";
			s_File << "\"ph\":\"X\",";
			s_File << String::Format("\"dur\":{},\"ts\":{},", end - start, start);
			s_File << String::Format("\"pid\":0,\"tid\":{}", threadID);
			s_File << "}";
		}
	};
}