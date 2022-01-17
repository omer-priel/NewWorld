#include "nwpch.h"
#include "GraphicsAPI.h"

#include <Windows.h>

namespace NewWorld::Core::GraphicsAPI
{
	void GraphicsAPI::Initialize()
	{
		SystemParametersInfoW(SPI_GETFOREGROUNDLOCKTIMEOUT, 0, &_glfw.win32.foregroundLockTimeout, 0);
		SystemParametersInfoW(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, UIntToPtr(0), SPIF_SENDCHANGE);

		// load Libraries
		LoadLibraryA("winmm.dll");
		LoadLibraryA("user32.dll");
		LoadLibraryA("dinput8.dll");
	}
}