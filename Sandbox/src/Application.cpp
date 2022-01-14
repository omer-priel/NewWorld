#include <NewWorld.h>
#include <NewWorld/EntryPoint.h>

#include "Settings.h"
#include "Tests/Tests.h"

namespace Sandbox
{
	class Application : NewWorld::Application
	{
	NW_CLASS(Sandbox, Application)

	public:
		Application()
		{
			
		}

		void Initialize() override
		{
			NewWorld::DataTypes::Threads::Thread::Sleap(500);
		}
	};
}

ENTRYPOINT_APPLICATION(Sandbox::Application);