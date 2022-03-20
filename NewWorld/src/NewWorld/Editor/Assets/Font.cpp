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
			return 37 + (uint)(character - 'a');
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
		
		return DEFUALT_CHARACTER_ID;
	}

	// Non-Static
	Font::Font(String dataAsset, String textureAsset)
		: m_Styles({ Style(false, false), Style(true, false), Style(false, true), Style(true, true) })
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

		file += sizeof(uint);

		for (size_t styleID = 0; styleID < STYLES_COUNT; styleID++)
		{
			Characters& characters = m_Styles[styleID].GetCharacters();
			for (size_t i = 0; i < CHARACTERS_COUNT; i++)
			{
				file >> characters[i].Name;
				file >> characters[i].AtlasX >> characters[i].AtlasY;
				file >> characters[i].Width >> characters[i].Height;
				file >> characters[i].OriginX >> characters[i].OriginY;
				file >> characters[i].PainterStepX;
			}
		}
	}

	Vector4 Font::GetDrawBounds(const String& text, uint fontSize, bool bold, bool italic, uint maxWidth) const
	{
		const Style& style = GetStyle(bold, italic);
		float sizeRatio = GetSizeRatio(fontSize);

		Vector4 bounds(0.0f);

		if (text.GetLength() == 0)
		{
			return bounds;
		}

		auto& firstCharacter = style.GetCharacter(text[0]);
		bounds.x = firstCharacter.OriginX;
		bounds.y = firstCharacter.OriginY;
		bounds.z = bounds.x + firstCharacter.Width;
		bounds.w = bounds.y + firstCharacter.Height;

		int panintedX = firstCharacter.PainterStepX;

		for (SizeT i = 1; i < text.GetLength(); i++)
		{
			auto& character = style.GetCharacter(text[i]);

			float x = character.OriginX + character.Width;
			
			float y1 = character.OriginY;
			float y2 = character.OriginY + character.Height;

			if (maxWidth > 0) {
				if ((panintedX + x) * sizeRatio > maxWidth)
				{
					return bounds * sizeRatio;
				}
			}

			bounds.z = panintedX + x;

			if (bounds.y > y1)
			{
				bounds.y = y1;
			}

			if (bounds.w < y2)
			{
				bounds.w = y2;
			}

			panintedX += character.PainterStepX;
		}

		return bounds * sizeRatio;
	}

}