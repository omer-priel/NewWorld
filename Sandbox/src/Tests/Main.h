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

			//NW_DEBUG("a: ", Object::GetType());

			NW_DEBUG("IDs: ", NewWorld::DataTypes::Build::c_LastTypeId);
		}
	}

	void TestsRoot()
	{
		Test1();

		system("pause");
	}
}