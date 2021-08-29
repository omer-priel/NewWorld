#include <NewWorld.h>
#include <NewWorld/EntryPoint.h>

#include "Tests/Main.h"

class Application : NewWorld::Application
{
public:
	Application() { }

	void Init() override { }

	void Test() override // TEMP
	{
		Tests::TestsRoot();
	}
};

ENTRYPOINT_APPLICATION(Application);