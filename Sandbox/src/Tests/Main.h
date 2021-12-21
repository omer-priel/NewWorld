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

			NW_DEBUG("a: ", NW_TYPE_ID(IObject));
			NW_DEBUG("b: ", NW_TYPE_ID(Object));
			NW_DEBUG("c: ", NW_TYPE_ID(String));
			NW_DEBUG("d: ", NW_TYPE_ID(Example));
			NW_DEBUG("e: ", NW_TYPE_ID(SharedPointer<String>));
			NW_DEBUG("f: ", NW_TYPE_ID(ScopePointer<String>));
			NW_DEBUG("a: ", NW_TYPE_ID(IObject));
			NW_DEBUG("b: ", NW_TYPE_ID(Object));
			NW_DEBUG("c: ", NW_TYPE_ID(String));
			NW_DEBUG("f: ", NW_TYPE_ID(ScopePointer<String>));
			NW_DEBUG("f: ", NW_TYPE_ID(ScopePointer<String>));

			NW_DEBUG("f1: ", NW_TYPE_ID(std::array<int, 1>));
			NW_DEBUG("f2: ", NW_TYPE_ID(std::array<int, 2>));
			NW_DEBUG("f3: ", NW_TYPE_ID(std::array<int, 3>));
			NW_DEBUG("f4: ", NW_TYPE_ID(std::array<int, 4>));
			NW_DEBUG("f5: ", NW_TYPE_ID(std::array<int, 5>));
			NW_DEBUG("f6: ", NW_TYPE_ID(std::array<int, 6>));
			NW_DEBUG("f7: ", NW_TYPE_ID(std::array<int, 7>));
			NW_DEBUG("f8: ", NW_TYPE_ID(std::array<int, 8>));
			NW_DEBUG("f9: ", NW_TYPE_ID(std::array<int, 9>));
			NW_DEBUG("f10: ", NW_TYPE_ID(std::array<int, 10>));
			NW_DEBUG("f11: ", NW_TYPE_ID(std::array<int, 11>));
			NW_DEBUG("f12: ", NW_TYPE_ID(std::array<int, 12>));
			NW_DEBUG("f13: ", NW_TYPE_ID(std::array<int, 13>));
			NW_DEBUG("f14: ", NW_TYPE_ID(std::array<int, 14>));
			NW_DEBUG("f15: ", NW_TYPE_ID(std::array<int, 15>));
			NW_DEBUG("f16: ", NW_TYPE_ID(std::array<int, 16>));
			NW_DEBUG("f17: ", NW_TYPE_ID(std::array<int, 17>));
			NW_DEBUG("f18: ", NW_TYPE_ID(std::array<int, 18>));
			NW_DEBUG("f19: ", NW_TYPE_ID(std::array<int, 19>));
			NW_DEBUG("f20: ", NW_TYPE_ID(std::array<int, 20>));
			NW_DEBUG("f21: ", NW_TYPE_ID(std::array<int, 21>));
			NW_DEBUG("f23: ", NW_TYPE_ID(std::array<int, 22>));
			NW_DEBUG("f24: ", NW_TYPE_ID(std::array<int, 23>));
			NW_DEBUG("f25: ", NW_TYPE_ID(std::array<int, 24>));
			NW_DEBUG("f26: ", NW_TYPE_ID(std::array<int, 26>));
			NW_DEBUG("f27: ", NW_TYPE_ID(std::array<int, 27>));
			NW_DEBUG("f28: ", NW_TYPE_ID(std::array<int, 28>));
			NW_DEBUG("f29: ", NW_TYPE_ID(std::array<int, 29>));
			NW_DEBUG("f30: ", NW_TYPE_ID(std::array<int, 30>));
			NW_DEBUG("f31: ", NW_TYPE_ID(std::array<int, 31>));
			NW_DEBUG("f32: ", NW_TYPE_ID(std::array<int, 32>));
			NW_DEBUG("f33: ", NW_TYPE_ID(std::array<int, 33>));
			NW_DEBUG("f34: ", NW_TYPE_ID(std::array<int, 34>));
			NW_DEBUG("f35: ", NW_TYPE_ID(std::array<int, 35>));
			NW_DEBUG("f36: ", NW_TYPE_ID(std::array<int, 36>));
			NW_DEBUG("f37: ", NW_TYPE_ID(std::array<int, 37>));
			NW_DEBUG("f38: ", NW_TYPE_ID(std::array<int, 38>));
			NW_DEBUG("f39: ", NW_TYPE_ID(std::array<int, 39>));

			NW_DEBUG("IDs: ", NewWorld::DataTypes::Build::c_LastTypeId);
		}
	}

	void TestsRoot()
	{
		Test1();

		system("pause");
	}
}