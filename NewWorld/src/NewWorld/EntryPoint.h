#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Core/Application.h"

#define ENTRYPOINT_APPLICATION(className) NewWorld::Application* CreateApplication() { return (NewWorld::Application*)new className(); }

NewWorld::Application* CreateApplication();

#if NW_PLATFORM_WINDOWS

int main(int argc, char* argv[])
{
	NewWorld::Application* application = CreateApplication();
	
	application->Init();

	application->Test(); // TEMP
	//application->Run();// TEMP
	
	delete application;
	return 0;
}

#else // Other PLATFORM
#error New World do not support this platform.
#endif