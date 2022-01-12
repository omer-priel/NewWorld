#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Files/File.h"

namespace NewWorld::Files
{
	// Friend of String
	class TextFile : public File
	{
	NW_CLASS(NewWorld::Files, TextFile)

	public:
		TextFile(const String& path, bool create = false, bool readOnly = false)
			: File(path, create, true, readOnly)
		{

		}

		// Read
	public:
		inline char Read()
		{
			return (char)ReadByte();
		}

		String ReadString(SizeT length)
		{
			String ret(length);
			m_Stream.read((char*)ret.GetPointer(), length);
			return ret;
		}

		inline void ReadLine(String& output)
		{
			std::getline(m_Stream, output.m_Value);
		}

		template <const SizeT LENGTH>
		void ReadLines(Array<String, LENGTH>& lines)
		{
			for (SizeT i = 0; i < LENGTH; i++)
			{
				ReadLine(lines[i]);
			}
		}

		inline String ReadAll()
		{
			return ReadString(GetSize() - GetIndex());
		}

		DynamicArray<String> ReadAllLines()
		{
			DynamicArray<String> lines;
			while (!IsLastByte())
			{
				String line;
				ReadLine(line);
				lines.push_back(line);
			}
			return lines;
		}

		TextFile& operator>>(char& output)
		{
			m_Stream.read((char*)&output, 1);
			return *this;
		}

		TextFile& operator>>(String& output)
		{
			ReadLine(output);
			return *this;
		}

		template <const SizeT LENGTH>
		TextFile& operator>>(Array<String, LENGTH>& lines)
		{
			ReadLines(lines);
			return *this;
		}

		// Write
	public:
		void Write(char value);

		void Write(const String& value);

		template <const SizeT LENGTH>
		void Write(const Array<String, LENGTH>& lines);
	};
}