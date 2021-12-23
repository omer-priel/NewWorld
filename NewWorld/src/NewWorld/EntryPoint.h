#pragma once

#include "NewWorld/Minimal.h"

#define ENTRYPOINT_APPLICATION(className) NewWorld::Application* CreateApplication() { return (NewWorld::Application*)new className(); }

NewWorld::Application* CreateApplication();

#if NW_PLATFORM_WINDOWS // Windows

int main(int argc, char* argv[])
{
	NewWorld::Application* application = CreateApplication();
	
	application->Init();

	application->Run();
	
	delete application;
	return 0;
}

#else // Other platforms
#error New World do not support this platform.
#endif