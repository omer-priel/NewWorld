#include <NewWorld.h>
#include <NewWorld/Math/Vector2.h>

#include "Example.h"

namespace Sandbox::Tests
{

	void Test1()
	{
		using namespace NewWorld;

		{
			NW_DEBUG("IDs: ", NewWorld::DataTypes::Build::c_LastTypeId);

			NW_DEBUG(Application::GetTypeStatic().GetStaticID());

			Math::Vector2 a;
		}
	}

	void TestsRoot()
	{
		Test1();

		system("pause");
	}
}