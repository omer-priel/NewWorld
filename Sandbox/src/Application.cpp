#include <NewWorld.h>
#include <NewWorld/EntryPoint.h>

#include <iostream>

class Application : NewWorld::Application
{
public:
	Application()
	{
		std::cout << "Application\n" << "\n";
	}
};

ENTRYPOINT_APPLICATION(Application);