#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Assets/Texture.h"
#include "NewWorld/Files/BinaryFile.h"

namespace NewWorld::Editor::Assets
{
	class Font : public Object
	{
	NW_CLASS(NewWorld::Editor::Assets, Font)
		
		// Constants
	public:
		static constexpr uint CHARACTERS_COUNT = 95;

		static constexpr uint DEFUALT_CHARACTER_ID = 75;
		static constexpr char DEFUALT_CHARACTER_CHAR = '?';

	private:
		static constexpr uint STYLES_COUNT = 4;

		// Subclasses
	public:
		class Character : public Object
		{
		NW_CLASS(NewWorld::Editor::Assets::Font, Character)

			// Members
		public:
			char Name;
			short AtlasX;
			short AtlasY;
			short Width;
			short Height;
			short OriginX;
			short OriginY;
			short PainterStepX;
		};

	public:
		using Characters = Array<Character, CHARACTERS_COUNT>;

	public:
		class Style : public Object
		{
		NW_CLASS(NewWorld::Editor::Assets::Font, Style)

			// Members
		private:
			bool m_Bold;
			bool m_Italic;

			Characters m_Characters;

		public:
			Style(bool bold, bool italic)
				: m_Bold(bold), m_Italic(italic) { }

			// Getters
		public:
			inline bool IsBold() const { return m_Bold; }
			inline bool IsItalic() const { return m_Italic; }

			inline const Character& GetCharacterByID(uint id) const
			{				
				if (id >= CHARACTERS_COUNT)
				{
					NW_WARN(NW_LOGGER_GRAPHICS, "The character id {} not exists!", id);

					id = DEFUALT_CHARACTER_ID;
				}

				return m_Characters[id];
			}

			inline const Character& GetCharacter(char character) const
			{
#if NW_CONFIG_DEBUG
				if (character != DEFUALT_CHARACTER_CHAR && GetCharacterID(character) == DEFUALT_CHARACTER_ID)
				{
					NW_WARN(NW_LOGGER_GRAPHICS, "The character \'{}\' not supported!", character);
				}
#endif
				return m_Characters[GetCharacterID(character)];
			}

			inline Characters& GetCharacters() { return m_Characters; }
		};

	public:
		using Styles = Array<Style, STYLES_COUNT>;

		// Static
	public:
		static uint GetCharacterID(char character);

		// Members
	private:
		String m_FamilyName;
		uint m_Size;

		Texture m_Texture;

		Styles m_Styles;

	public:
		Font(String dataAsset, String textureAsset);
		
		// Getters
	public:
		inline uint GetSize() const { return m_Size; }

		inline const Texture& GetTexture() const { return m_Texture; }

		inline const Style& GetStyle(bool bold, bool italic) const
		{
			return m_Styles[bold + italic * 2];
		}

		inline const Character& GetCharacterByID(uint id, bool bold, bool italic) const
		{
			return GetStyle(bold, italic).GetCharacterByID(id);
		}

		inline const Character& GetCharacter(char character, bool bold, bool italic) const
		{
			return GetStyle(bold, italic).GetCharacter(character);
		}

		// Actions
	public:
		inline float GetSizeRatio(uint fontSize) const
		{
			return ((float)fontSize * 5.0f / 3.0f) / ((float)m_Size);
		}

		Vector4 GetDrawBounds(const String& text, uint fontSize, bool bold, bool italic, uint maxWidth) const;
	};
}