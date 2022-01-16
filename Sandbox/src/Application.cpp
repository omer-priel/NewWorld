#include <NewWorld.h>
#include <NewWorld/EntryPoint.h>

#include "Settings.h"
#include "Tests/Tests.h"

namespace Sandbox
{
	void PrintMe()
	{
		DEBUG(MAIN_LOGGER, "msg:");
	}

	class Application : NewWorld::Application
	{
	NW_CLASS(Sandbox, Application)

	public:
		Application()
		{
			
		}

		void Initialize() override
		{
			NewWorld::Function<void> func = &PrintMe;
			func();
		}
	};
}

ENTRYPOINT_APPLICATION(Sandbox::Application);