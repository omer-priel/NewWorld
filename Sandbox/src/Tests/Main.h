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
			NW_DEBUG("a: ", Generator<IObject>::ID);
			NW_DEBUG("b: ", Generator<Object>::ID);
			NW_DEBUG("c: ", Generator<String>::ID);
			NW_DEBUG("f: ", Generator<ScopePointer<String>>::ID);
			NW_DEBUG("f: ", Generator<ScopePointer<String>>::ID);
			
			NW_DEBUG("f1: ", Generator<std::array<int, 1>>::ID);
			NW_DEBUG("f2: ", Generator<std::array<int, 2>>::ID);
			NW_DEBUG("f3: ", Generator<std::array<int, 3>>::ID);
			NW_DEBUG("f4: ", Generator<std::array<int, 4>>::ID);
			NW_DEBUG("f5: ", Generator<std::array<int, 5>>::ID);
			NW_DEBUG("f6: ", Generator<std::array<int, 6>>::ID);
			NW_DEBUG("f7: ", Generator<std::array<int, 7>>::ID);
			NW_DEBUG("f8: ", Generator<std::array<int, 8>>::ID);
			NW_DEBUG("f9: ", Generator<std::array<int, 9>>::ID);
			NW_DEBUG("f10: ", Generator<std::array<int, 10>>::ID);
			NW_DEBUG("f11: ", Generator<std::array<int, 11>>::ID);
			NW_DEBUG("f12: ", Generator<std::array<int, 12>>::ID);
			NW_DEBUG("f13: ", Generator<std::array<int, 13>>::ID);
			NW_DEBUG("f14: ", Generator<std::array<int, 14>>::ID);
			NW_DEBUG("f15: ", Generator<std::array<int, 15>>::ID);
			NW_DEBUG("f16: ", Generator<std::array<int, 16>>::ID);
			NW_DEBUG("f17: ", Generator<std::array<int, 17>>::ID);
			NW_DEBUG("f18: ", Generator<std::array<int, 18>>::ID);
			NW_DEBUG("f19: ", Generator<std::array<int, 19>>::ID);
			NW_DEBUG("f20: ", Generator<std::array<int, 20>>::ID);
			NW_DEBUG("f21: ", Generator<std::array<int, 21>>::ID);
			NW_DEBUG("f23: ", Generator<std::array<int, 22>>::ID);
			NW_DEBUG("f24: ", Generator<std::array<int, 23>>::ID);
			NW_DEBUG("f25: ", Generator<std::array<int, 24>>::ID);
			NW_DEBUG("f26: ", Generator<std::array<int, 26>>::ID);
			NW_DEBUG("f27: ", Generator<std::array<int, 27>>::ID);
			NW_DEBUG("f28: ", Generator<std::array<int, 28>>::ID);
			NW_DEBUG("f29: ", Generator<std::array<int, 29>>::ID);
			NW_DEBUG("f30: ", Generator<std::array<int, 30>>::ID);
			NW_DEBUG("f31: ", Generator<std::array<int, 31>>::ID);
			NW_DEBUG("f32: ", Generator<std::array<int, 32>>::ID);
			NW_DEBUG("f33: ", Generator<std::array<int, 33>>::ID);
			NW_DEBUG("f34: ", Generator<std::array<int, 34>>::ID);
			NW_DEBUG("f35: ", Generator<std::array<int, 35>>::ID);
			NW_DEBUG("f36: ", Generator<std::array<int, 36>>::ID);
			NW_DEBUG("f37: ", Generator<std::array<int, 37>>::ID);
			NW_DEBUG("f38: ", Generator<std::array<int, 38>>::ID);
			NW_DEBUG("f39: ", Generator<std::array<int, 39>>::ID);


			NW_DEBUG(ptr, " ", ptr2, "\n", ptr.GetType());
		}
	}

	void TestsRoot()
	{
		Test1();

		system("pause");
	}
}