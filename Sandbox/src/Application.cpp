#include <NewWorld.h>
#include <NewWorld/EntryPoint.h>

#include "Settings.h"
#include "Tests/Tests.h"

namespace Sandbox
{
	static int x = 0;

	void TaskA2();

	void TaskA()
	{
		NW_PROFILE_SCOPE("TaskA");
		NewWorld::DataTypes::Thread::Sleap(10);

		NewWorld::DataTypes::Thread subTask(TaskA2);
		while (x % 100 < 5)
		{
			NW_PROFILE_SCOPE("TaskA Frame");
			DEBUG(MAIN_LOGGER, "TaskA {} {}", NewWorld::DataTypes::Thread::GetThisThreadID(), x);
			x += 1;
			NewWorld::DataTypes::Thread::Sleap(1000);
		}
		subTask.Start();
		subTask.Wait();
	}

	void TaskA2()
	{
		NW_PROFILE_SCOPE("TaskA2");
		NewWorld::DataTypes::Thread::Sleap(10);

		while (x % 100 < 10)
		{
			NW_PROFILE_SCOPE("TaskA2 Frame");
			DEBUG(MAIN_LOGGER, "TaskA2 {} {}", NewWorld::DataTypes::Thread::GetThisThreadID(), x);
			x += 1;
			NewWorld::DataTypes::Thread::Sleap(1000);
		}
	}

	void TaskB()
	{
		NW_PROFILE_SCOPE("TaskB");
		NewWorld::DataTypes::Thread::Sleap(10);

		while (x / 1000 < 12)
		{
			NW_PROFILE_SCOPE("TaskB Frame");
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
			: tr(TaskA), tr2(TaskB)
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