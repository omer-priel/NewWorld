#include "nwpch.h"
#include "Shader.h"

#include "NewWorld/Files/FileManager.h"
#include "NewWorld/Files/BinaryFile.h"

namespace NewWorld::Editor::Assets
{
	bool Shader::LoadFromFile(String asset)
	{
		String filepath = Files::FileManager::GetAssetPath(asset);

		Files::BinaryFile reader(filepath, false, true);

		reader >> m_Source.VertexPartLength;
		if (m_Source.VertexPartLength > 0)
		{
			m_Source.VertexPartSource = new Byte[m_Source.VertexPartLength];
			reader.Read(m_Source.VertexPartSource, m_Source.VertexPartLength);
		}

		reader >> m_Source.FragmentPartLength;
		if (m_Source.FragmentPartLength > 0)
		{
			m_Source.FragmentPartSource = new Byte[m_Source.FragmentPartLength];
			reader.Read(m_Source.FragmentPartSource, m_Source.FragmentPartLength);
		}

		m_Loaded = true;

		return IsLoaded();
	}
}