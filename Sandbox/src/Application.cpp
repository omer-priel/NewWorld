#include <NewWorld.h>

// TEMP
#define SELECT_APPLICATION(x);

SELECT_APPLICATION(App);

class Application : NewWorld::Application
{
	Application()
	{

	}
};

#include "NewWorld/Core/EntryPoint.h"