#include <NewWorld.h>
#include <NewWorld/EntryPoint.h>

#include "Settings.h"
#include "Tests/Main.h"

namespace Sandbox
{
	class Application : NewWorld::Application
	{
		NW_CLASS(Sandbox, Application)

	public:
		Application()
		{
			//GetLoggerManager().SetLogger(MAIN_LOGGER, "SandBox");
			//GetLoggerManager().SetLogger(TESTS_LOGGER, "Tests");
		}

		void Init() override
		{
			Tests::TestsRoot();
		}
	};
}

ENTRYPOINT_APPLICATION(Sandbox::Application);