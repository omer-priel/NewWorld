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

		// Getters
	public:
		SharedPointer<Shader> GetShader(uint id);

		SizeT GetShadersCount() const { return (SizeT)m_Shaders.size(); };

		// Actions
	public:
		int LoadShader(String asset);
	};
}