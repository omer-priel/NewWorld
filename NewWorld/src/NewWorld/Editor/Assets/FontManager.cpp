#include "nwpch.h"
#include "FontManager.h"

namespace NewWorld::Editor::Assets
{
	int FontManager::LoadFont(String dataAsset, String textureAsset)
	{
		SharedPointer<Font> font(dataAsset, textureAsset);
		
		m_Fonts.push_back(font);

		return (int)(m_Fonts.size() - 1);
	}

	SharedPointer<Font> FontManager::GetFont(int id)
	{
		NW_ASSERT(0 <= id && id < m_Fonts.size(), "The Font id {} not found!", id);

		return m_Fonts[id];
	}
}