#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Assets/Texture.h"
#include "NewWorld/Files/BinaryFile.h"

namespace NewWorld::Editor::Assets
{
	class Font : public Object
	{
	NW_CLASS(NewWorld::Editor::Assets, Font)
		
		// Subclasses
	public:
		class Character : public Object
		{
		NW_CLASS(NewWorld::Editor::Assets::Font, Character)

			// Members
		public:
			char Name;
			int AtlasX;
			int AtlasY;
			int Width;
			int Height;
			int OriginX;
			int OriginY;
			int PainterStepX;
		};

		// Constants
	public:
		static constexpr uint CHARACTERS_COUNT = 95;

		// Static
	public:
		static uint GetCharacterID(char character);

		// Members
	private:
		String m_FamilyName;
		uint m_Size;
		bool m_Bold;
		bool m_Italic;
		uint m_Width;
		uint m_Height;
		Array<Character, CHARACTERS_COUNT> m_Characters;

		Texture m_Texture;

	public:
		Font(String textureAsset, String dataAsset);
		
		// Getters
	public:
		inline uint GetSize() const { return m_Size; }
		inline bool IsBold() const { return m_Bold; }
		inline bool IsItalic() const { return m_Italic; }
		inline uint GetWidth() const { return m_Width; }
		inline uint GetHeight() const { return m_Height; }

		inline const Texture& GetTexture() const { return m_Texture; }

		inline const Character& GetCharacterByID(uint id) const
		{
			NW_ASSERT(id < CHARACTERS_COUNT, "The character id not exists!");

			return m_Characters[id];
		}

		inline const Character& GetCharacter(char character) const
		{
			return m_Characters[GetCharacterID(character)];
		}
	};
}