#pragma once
#include "NewWorld/Minimal.h"
#include "NewWorld/Core/Application.h"

#if NW_PLATFORM_WINDOWS

int main(int argc, char* argv[])
{
	//TEMP: new ...
	NewWorld::Application* application = new NewWorld::Application();
	
	application->Run();
	
	delete application;
	return 0;
}

#else // Other PLATFORM
#error New World do not support this platform.
#endif