#include <NewWorld.h>
#include <NewWorld/EntryPoint.h>

#include "Settings.h"
#include "Tests/Tests.h"

namespace Sandbox
{
	static int x = 0;

	void TaskA()
	{
		while (x % 10 < 5)
		{
			NW_PROFILE_SCOPE("TaskA");
			DEBUG(MAIN_LOGGER, "TaskA {} {}", NewWorld::DataTypes::Thread::GetThisThreadID(), x);
			x += 1;
			NewWorld::DataTypes::Thread::Sleap(1000);
		}
	}

	void TaskB()
	{
		while (true)
		{
			NW_PROFILE_SCOPE("TaskB");
			DEBUG(MAIN_LOGGER, "TaskB {} {}", NewWorld::DataTypes::Thread::GetThisThreadID(), x);
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
			: tr(TaskB), tr2(TaskB)
		{
			
		}

		void Initialize() override
		{
			tr.Start();
			tr2.Start();

			while (true)
			{
				DEBUG(MAIN_LOGGER, "T--- {} {}", tr, tr2);
				NewWorld::DataTypes::Thread::Sleap(2000);
			}
		}
	};
}

ENTRYPOINT_APPLICATION(Sandbox::Application);