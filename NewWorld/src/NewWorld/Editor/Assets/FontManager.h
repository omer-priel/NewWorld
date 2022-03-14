#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Assets/Font.h"

namespace NewWorld::Editor::Assets
{
	class FontManager : public Object
	{
	NW_CLASS(NewWorld::Editor::Assets, FontManager)

		// Members
	private:
		DynamicArray<SharedPointer<Font>> m_Fonts;

	public:
		FontManager()
			: m_Fonts()
		{

		}

		// Load
	public:
		int LoadFont(String textureAsset, String dataAsset);
		
		// Getters
	public:
		SharedPointer<Font> GetFont(int id);
	};
}