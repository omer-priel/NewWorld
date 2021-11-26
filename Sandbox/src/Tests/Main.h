#include <NewWorld.h>

#include <NewWorld/DataTypes/Build/ConstantCounter.h>

#include "Example.h"

namespace Sandbox::Tests
{
	void Test1()
	{
		using namespace NewWorld;

		{
			SharedPointer<String> ptr("Test1");
			ScopePointer<String> ptr2("Test2");

			NW_DEBUG("a: ", Generator<IObject>::ID);
			NW_DEBUG("b: ", Generator<Object>::ID);
			NW_DEBUG("c: ", Generator<String>::ID);
			NW_DEBUG("d: ", Generator<Example>::ID);
			NW_DEBUG("e: ", Generator<SharedPointer<String>>::ID);
			NW_DEBUG("f: ", Generator<ScopePointer<String>>::ID);
			NW_DEBUG("g: ", Generator<IObject>::ID);
			NW_DEBUG("h: ", Generator<Object>::ID);
			NW_DEBUG("i: ", Generator<String>::ID);

			NW_DEBUG(ptr, " ", ptr2, "\n", ptr.GetType());
		}
	}

	void TestsRoot()
	{
		Test1();

		system("pause");
	}
}