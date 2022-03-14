#include "nwpch.h"
#include "Font.h"

namespace NewWorld::Editor::Assets
{
	// Static
	uint Font::GetCharacterID(char character)
	{
		if ('0' <= character && character <= '9')
		{
			return 0 + (uint)(character - '0');
		}

		if ('A' <= character && character <= 'Z')
		{
			return 11 + (uint)(character - 'A');
		}
		if ('a' <= character && character <= 'z')
		{
			return 46 + (uint)(character - 'a');
		}

		switch (character)
		{
			case ' ': return 10;
			case '!': return 63;
			case '"': return 64;
			case '#': return 65;
			case '$': return 66;
			case '%': return 67;
			case '&': return 68;
			case ',': return 69;
			case '.': return 70;
			case ':': return 71;
			case ';': return 72;
			case '<': return 73;
			case '>': return 74;
			case '?': return 75;
			case '@': return 76;
			case '[': return 77;
			case ']': return 78;
			case '\\': return 79;
			case '/': return 80;
			case '|': return 81;
			case '^': return 82;
			case '_': return 83;
			case '`': return 84;
			case '{': return 85;
			case '}': return 86;
			case '~': return 87;
			case '\'': return 88;
			case '(': return 89;
			case ')': return 90;
			case '*': return 91;
			case '+': return 92;
			case '-': return 93;
			case '=': return 94;
		}

		NW_WARN(NW_LOGGER_GRAPHICS, "The character \'{}\' not supported!", character);
		
		return GetCharacterID('?');
	}

	// Non-Static
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