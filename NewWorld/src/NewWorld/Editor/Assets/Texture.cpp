#include "nwpch.h"
#include "Texture.h"

#include "NewWorld/Files/FileManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "NewWorld/Dependencies/stb_image/stb_image.h"

namespace NewWorld::Editor::Assets
{
	bool Texture::LoadFromPNGFile(String asset)
	{
		String filepath = Files::FileManager::GetAssetPath(asset);

		stbi_set_flip_vertically_on_load(1);
		m_Data = stbi_load(filepath.GetPointer(), &m_Width, &m_Height, &m_Channels, 4);

#if NW_CONFIG_DEBUG
		if (stbi_failure_reason())
		{
			NW_ERROR(NW_LOGGER_GRAPHICS, "stbi failure: {}", stbi_failure_reason());
		}

#endif

		return IsLoaded();
	}
}