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

		String path = Files::FileManager::GetRootDirectory("profile.json");

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
		uint threadID = DataTypes::Thread::GetThisThreadID();

		name.Replace('"', '\'');

		s_File << String::Format("{}{\"name\":\"{}\",\"cat\":\"Event\",\"ph\":\"X\",\"dur\":100,\"ts\":{},\"pid\":0,\"tid\":{}}",
			s_IsFirstEvent ? "" : ",", name, Time::Now().GetTicks(), threadID);

		if (s_IsFirstEvent)
		{
			s_IsFirstEvent = false;
		}
	}

	void Profiler::AddScope(String name, Ulong start, Ulong end)
	{
		uint threadID = DataTypes::Thread::GetThisThreadID();

		name.Replace('"', '\'');

		s_File << String::Format("{}{\"name\":\"{}\",\"cat\":\"Scope\",\"ph\":\"X\",\"dur\":{},\"ts\":{},\"pid\":0,\"tid\":{}}",
			s_IsFirstEvent ? "" : ",", name, end - start, start, threadID);

		if (s_IsFirstEvent)
		{
			s_IsFirstEvent = false;
		}
	}
}