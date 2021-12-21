#include <NewWorld.h>

#include "Example.h"

namespace Sandbox::Tests
{

	void Test1()
	{
		using namespace NewWorld;

		{
			NW_DEBUG("IDs: ", NewWorld::DataTypes::Build::c_LastTypeId);

			NW_DEBUG(Application::GetTypeStatic().GetStaticID());

		}
	}

	void TestsRoot()
	{
		Test1();

		system("pause");
	}
}