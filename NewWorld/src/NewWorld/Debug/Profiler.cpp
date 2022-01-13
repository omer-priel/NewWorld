#include "nwpch.h"
#include "Profiler.h"

namespace NewWorld::Debug
{
	// Members
	Files::TextFile Profiler::s_File;
	bool Profiler::s_IsFirstEvent;

	// Actions
	void Profiler::Initialize()
	{
		s_IsFirstEvent = true;

		String path = Files::FileManger::GetRootDirectory("profile.json");

		Files::File::Delete(path);
		s_File.Open(path, true);

		s_File << "{\"displayTimeUnit\":\"ms\",";
		s_File << "\"otherData\": {},\"traceEvents\":[";
	}

	void Profiler::Finalize()
	{
		s_File << "]}";
		s_File.Close();
	}

	void Profiler::AddEvent(String name)
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
		s_File << String::Format("\"dur\":100,\"ts\":{},", Time::Now().GetTicks());
		s_File << String::Format("\"pid\":0,\"tid\":{}", threadID);
		s_File << "}";
	}

	void Profiler::AddScope(String name, Ulong start, Ulong end)
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
		s_File << "\"cat\":\"Scope\",";
		s_File << "\"ph\":\"X\",";
		s_File << String::Format("\"dur\":{},\"ts\":{},", end - start, start);
		s_File << String::Format("\"pid\":0,\"tid\":{}", threadID);
		s_File << "}";
	}
}