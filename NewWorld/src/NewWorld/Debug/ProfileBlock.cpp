#include "nwpch.h"
#include "ProfileBlock.h"

namespace NewWorld::Debug
{
	ProfileBlock::ProfileBlock(const String& name)
		: m_Name(name), m_Start(Time::Now().GetTicks())
	{

	}

	ProfileBlock::~ProfileBlock()
	{
		Profiler::AddBlock(m_Name, m_Start, Time::Now().GetTicks());
	}
}