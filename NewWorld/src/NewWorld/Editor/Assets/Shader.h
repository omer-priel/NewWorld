#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Editor::Assets
{
	class Shader : public Object
	{
	NW_CLASS(NewWorld::Editor::Assets, Shader)

		// Sub-classes
	public:
		class ShaderSource : public Object
		{
		NW_CLASS(NewWorld::Editor::Assets::Shader, ShaderSource)

			// Members
		public:
			int VertexPartLength = 0;
			Byte* VertexPartSource = nullptr;

			int GeometryPartLength = 0;
			Byte* GeometryPartSource = nullptr;

			int FragmentPartLength = 0;
			Byte* FragmentPartSource = nullptr;
		};

		// Members
	private:
		ShaderSource m_Source;
		bool m_Loaded;

		uint m_ProgramHandler = 0;

	public:
		Shader()
		: m_Loaded(false) { }

		// Getters
	public:
		inline bool IsLoaded() const { return m_Loaded; }

		inline const ShaderSource& GetSource() const { return m_Source; }

		int GetUniformLocation(const String& name);

		// Load
	public:
		bool LoadFromFile(String asset);

		// Actions
	public:
		void Compile();

		void Use();

		// Actions
	private:
		inline uint CompilePart(uint partID, uint partType, const Byte* partSource, int partLength);
	};
}