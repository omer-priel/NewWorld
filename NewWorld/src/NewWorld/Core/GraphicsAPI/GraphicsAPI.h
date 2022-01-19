#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Core::GraphicsAPI
{
	// This is static class
	class GraphicsAPI : public Object
	{
	NW_CLASS(NewWorld::Core::GraphicsAPI, GraphicsAPI)

		// Init
	public:
		static void Initialize();
		static void Finalize();
	};
}