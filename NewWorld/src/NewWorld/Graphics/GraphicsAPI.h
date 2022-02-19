#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Graphics
{
	// This is static class
	class GraphicsAPI : public Object
	{
	NW_CLASS(NewWorld::Graphics, GraphicsAPI)

		// Init
	public:
		static void Initialize();
		static void Finalize();
	};
}