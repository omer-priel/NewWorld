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
		static void Initialize();
		static void Finalize();

		static void AddEvent(String name);
		static void AddScope(String name, Ulong start, Ulong end);
	};
}