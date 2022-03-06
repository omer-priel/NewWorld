#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Assets/Shader.h"

namespace NewWorld::Editor::Assets
{
	class ShaderManager : public Object
	{
	NW_CLASS(NewWorld::Editor::Assets, ShaderManager)

		// Members
	private:
		DynamicArray<SharedPointer<Shader>> m_Shaders;

	public:
		ShaderManager()
			: m_Shaders()
		{

		}

		// Load Textures
	public:
		int LoadShader(String asset);

	public:
		// Get Texture
		SharedPointer<Shader> GetShader(int id);
	};
}