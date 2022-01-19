#pragma once

#include "NewWorld/Minimal.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace NewWorld::Math::Projection
{
	inline Matrix4 OrthographicMatrix(uint xMin, uint yMin, uint xMax, uint yMax)
	{
		return glm::ortho(xMin, xMax, yMin, yMax);
	}
}