#include <NewWorld.h>

#include "Example.h"

namespace Sandbox::Tests
{
	void PrintType(NewWorld::DataTypes::Type type)
	{
		NW_DEBUG(type.GetStaticID(), " is from the class ", type.GetName());
	}

	void Test1()
	{
		using namespace NewWorld;

		{
			NW_DEBUG("IDs: ", NewWorld::DataTypes::Build::c_LastTypeId);

			SharedPointer<String> ptr("Test1");
			ScopePointer<String> ptr2("Test2");

			NW_DEBUG(ptr, " ", ptr2, "\n", ptr.GetType());

			PrintType(Object::GetTypeStatic());
			PrintType(String::GetTypeStatic());
			PrintType(Example::GetTypeStatic());
			PrintType(SharedPointer<String>::GetTypeStatic());
			PrintType(ScopePointer<String>::GetTypeStatic());
			PrintType(SharedPointer<Example>::GetTypeStatic());
			PrintType(ScopePointer<ScopePointer<Example>>::GetTypeStatic());

			PrintType(ptr.GetType());
			PrintType(ptr2.GetType());
		}
	}

	void TestsRoot()
	{
		Test1();

		system("pause");
	}
}