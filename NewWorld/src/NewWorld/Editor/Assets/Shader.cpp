#include "nwpch.h"
#include "Shader.h"

#include "NewWorld/Files/FileManager.h"
#include "NewWorld/Files/BinaryFile.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

		reader >> m_Source.GeometryPartLength;
		if (m_Source.GeometryPartLength > 0)
		{
			m_Source.GeometryPartSource = new Byte[m_Source.GeometryPartLength];
			reader.Read(m_Source.GeometryPartSource, m_Source.GeometryPartLength);
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

	void Shader::Compile()
	{
		m_ProgramHandler = glCreateProgram();

		uint s1 = CompilePart(GL_VERTEX_SHADER, m_Source.VertexPartSource, m_Source.VertexPartLength);
		uint s2 = CompilePart(GL_GEOMETRY_SHADER, m_Source.GeometryPartSource, m_Source.GeometryPartLength);
		uint s3 = CompilePart(GL_FRAGMENT_SHADER, m_Source.FragmentPartSource, m_Source.FragmentPartLength);

		glLinkProgram(m_ProgramHandler);
		glValidateProgram(m_ProgramHandler);

		if (s1) { glDeleteShader(s1); }
		if (s2) { glDeleteShader(s2); }
		if (s3) { glDeleteShader(s3); }
	}

	uint Shader::CompilePart(uint partType, const Byte* partSource, int partLength)
	{
		if (partLength > 0)
		{
			uint id = glCreateShader(partType);
			glShaderSource(id, 1, (const GLchar**)&partSource, &partLength);
			glCompileShader(id);

#if NW_CONFIG_DEBUG
			int result;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				int length;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

				String message(length);
				glGetShaderInfoLog(id, length, &length, (GLchar*)message.GetPointer());

				NW_ERROR(NW_LOGGER_GRAPHICS, "Shader Compile Error: {}", message);

				glDeleteShader(id);

				return 0;
			}
#endif
			glAttachShader(m_ProgramHandler, id);

			return id;
		}

		return 0;
	}

	void Shader::Use()
	{
		glUseProgram(m_ProgramHandler);
	}

	int Shader::GetUniformLocation(const String& name)
	{
		return glGetUniformLocation(m_ProgramHandler, name.GetPointer());
	}
}