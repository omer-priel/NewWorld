#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Assets/Texture.h"

namespace NewWorld::Editor::Assets
{
	class TextureManger : public Object
	{
	NW_CLASS(NewWorld::Editor::Assets, TextureManger)

		// Members
	private:
		DynamicArray<SharedPointer<Texture>> m_Textures;

	public:
		TextureManger()
			: m_Textures()
		{

		}

		// Load Textures
	public:
		SharedPointer<Texture> LoadTexture(String name);
		
		SharedPointer<Texture> LoadPNG(String name);

	public:
		// Get Texture
		SharedPointer<Texture> GetTexture(uint id);
	};
}