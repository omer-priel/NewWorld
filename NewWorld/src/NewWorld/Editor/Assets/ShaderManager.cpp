#include "nwpch.h"
#include "ShaderManager.h"

#include "NewWorld/Files/FileManager.h"

namespace NewWorld::Editor::Assets
{
		int ShaderManager::LoadShader(String asset)
	{
		SharedPointer<Shader> shader;
		bool loaded = shader->LoadFromFile(asset);
		
		if (loaded)
		{
			m_Shaders.push_back(shader);
			return m_Shaders.size() - 1;
		}

		return -1;
	}

	SharedPointer<Shader> ShaderManager::GetShader(int id)
	{
		NW_ASSERT(0 <= id && id < m_Shaders.size(), "The Shader id {} not found!");

		return m_Shaders[id];
	}
}