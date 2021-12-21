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

			Vector2 a(1, 2);
			Vector2 b(3, 4);
			Vector3 c(1, 2, 3);
			Vector4 d(a, b);

			NW_DEBUG(a, " ", b, " ", c, " ", d);
			NW_DEBUG(d * d);
			NW_DEBUG(a + b);
		}
	}

	void TestsRoot()
	{
		Test1();

		system("pause");
	}
}