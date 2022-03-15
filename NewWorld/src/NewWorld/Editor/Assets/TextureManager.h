#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Assets/Texture.h"

namespace NewWorld::Editor::Assets
{
	class TextureManager : public Object
	{
	NW_CLASS(NewWorld::Editor::Assets, TextureManager)

		// Members
	private:
		DynamicArray<SharedPointer<Texture>> m_Textures;

	public:
		TextureManager()
			: m_Textures()
		{

		}

		// Load Textures
	public:
		int LoadTexture(String asset);
		
	public:
		// Get Texture
		SharedPointer<Texture> GetTexture(int id);
	};
}