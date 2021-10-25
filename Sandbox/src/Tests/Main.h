#include <NewWorld.h>

#include "Example.h"

namespace Sandbox::Tests
{
	void Test1()
	{
		using namespace NewWorld;

		{
			SharedPointer<String> ptr("Test1");
			ScopePointer<String> ptr2("Test2");

			NW_DEBUG(ptr, " ", ptr2, "\n", ptr.GetType());
		}
	}

	void TestsRoot()
	{
		Test1();

		system("pause");
	}
}