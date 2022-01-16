#include <NewWorld.h>
#include <NewWorld/EntryPoint.h>

#include "Settings.h"
#include "Tests/Tests.h"

namespace Sandbox
{
	static int x = 0;

	void A()
	{
		while (true)
		{
			DEBUG(MAIN_LOGGER, "A {}", x);
			x += 1;
			NewWorld::DataTypes::Thread::Sleap(1000);
		}
	}

	void B()
	{
		while (true)
		{
			DEBUG(MAIN_LOGGER, "B {}", x);
			x += 1000;
			NewWorld::DataTypes::Thread::Sleap(2000);
		}
	}

	class Application : NewWorld::Application
	{
	NW_CLASS(Sandbox, Application)

	public:
		NewWorld::DataTypes::Thread tr;
		NewWorld::DataTypes::Thread tr2;

	public:
		Application()
			: tr(A), tr2(B)
		{
			
		}

		void Initialize() override
		{
			tr.Start();
			tr2.Start();
		}
	};
}

ENTRYPOINT_APPLICATION(Sandbox::Application);