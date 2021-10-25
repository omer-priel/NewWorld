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

			constexpr int a = Generator<IObject>::ID;
			constexpr int b = Generator<Object>::ID;
			constexpr int c = Generator<String>::ID;
			constexpr int d = Generator<Object>::ID;
			constexpr int e = Generator<IObject>::ID;

			NW_DEBUG("IObject: ", a);
			NW_DEBUG("Object: ", b);
			NW_DEBUG("String: ", c);
			NW_DEBUG("d: ", d);
			NW_DEBUG("e: ", e);

			NW_DEBUG(ptr, " ", ptr2, "\n", ptr.GetType());
		}
	}

	void TestsRoot()
	{
		Test1();

		system("pause");
	}
}