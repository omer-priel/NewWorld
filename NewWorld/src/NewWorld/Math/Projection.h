#pragma once

#include "NewWorld/Minimal.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace NewWorld::Math::Projection
{
	inline glm::mat4 OrthographicMatrix(float left, float right, float bottom, float top)
	{
		return glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		//return glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
		//return glm::ortho((float)xMin, (float)xMax, (float)yMin, (float)yMax, -1.0f, 1.0f);
	}
}