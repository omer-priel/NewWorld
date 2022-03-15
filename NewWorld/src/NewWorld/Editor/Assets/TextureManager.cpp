#include "nwpch.h"
#include "TextureManager.h"

namespace NewWorld::Editor::Assets
{
	int TextureManager::LoadTexture(String asset)
	{
		SharedPointer<Texture> texture;
		bool loaded = texture->LoadFromPNGFile(asset);
		
		if (loaded)
		{
			m_Textures.push_back(texture);
			return m_Textures.size() - 1;
		}

		return -1;
	}

	SharedPointer<Texture> TextureManager::GetTexture(int id)
	{
		NW_ASSERT(0 <= id && id < m_Textures.size(), "The Texture id {} not found!");

		return m_Textures[id];
	}
}