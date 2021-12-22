#include <NewWorld.h>
#include <NewWorld/EntryPoint.h>

#include "Tests/Main.h"

namespace Sandbox
{
	class Application : NewWorld::Application
	{
		NW_CLASS(Sandbox, Application)

	public:
		Application() { }

		void Init() override
		{
			Tests::TestsRoot();
		}
	};
}

ENTRYPOINT_APPLICATION(Sandbox::Application);