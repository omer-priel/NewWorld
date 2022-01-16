#include "nwpch.h"
#include "Thread.h"

namespace NewWorld::DataTypes
{
	// Thread Local Storge
	thread_local uint s_ThreadID = 1;

	// Static Members
	uint Thread::s_LastID = 1;

	// Static
	uint Thread::GetThisThreadID()
	{
		return s_ThreadID;
	}

	void Thread::FullFunc(uint threadID, Func func)
	{
		s_ThreadID = threadID;
		func();
	}
}