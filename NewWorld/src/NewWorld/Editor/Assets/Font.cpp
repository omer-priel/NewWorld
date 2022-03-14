#include "nwpch.h"
#include "Font.h"

namespace NewWorld::Editor::Assets
{
	Font::Font(String textureAsset, String dataAsset)
	{
		// Load the Texture
		m_Texture.LoadFromPNGFile(textureAsset);

		NW_ASSERT(m_Texture.IsLoaded(), "Faild to load the texture of the font!");

		// Load the Data
		String filepath = Files::FileManager::GetAssetPath(dataAsset);
		Files::BinaryFile file(filepath, false, true);

		NW_ASSERT(file.IsOpened(), "Faild to load the data file of the font!");

		uint familyNameLength;
		file >> familyNameLength;

		m_FamilyName.Resize(familyNameLength);

		file.Read((Byte*)m_FamilyName.GetPointer(), familyNameLength);

		file >> m_Size;
		file >> m_Bold >> m_Italic;
		file >> m_Width >> m_Height;

		file += sizeof(uint);

		for (size_t i = 0; i < CHARACTERS_COUNT; i++)
		{
			file >> m_Characters[i].Name;
			file >> m_Characters[i].AtlasX >> m_Characters[i].AtlasY;
			file >> m_Characters[i].Width >> m_Characters[i].Height;
			file >> m_Characters[i].OriginX >> m_Characters[i].OriginY;
			file >> m_Characters[i].PainterStepX;
		}
	}

}