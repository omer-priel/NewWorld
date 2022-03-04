#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Editor::Assets
{
	class Texture : public Object
	{
	NW_CLASS(NewWorld::Editor::Assets, Texture)

		// Members
	private:
		int m_Width;
		int m_Height;
		int m_Channels;
		Byte* m_Data;

	public:
		Texture() 
		: m_Width(0), m_Height(0), m_Channels(0), m_Data(nullptr) {}
		
		// Getters
	public:
		inline bool IsLoaded() const { return m_Data == nullptr; }

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
		inline int GetChannels() const { return m_Channels; }

		inline const Byte* const GetData() const { return m_Data; }

		// Load
	public:
		bool LoadFromPNGFile(String asset);
	};
}