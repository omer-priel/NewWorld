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
		inline void Write(char value)
		{
			m_Stream.clear();
			m_Stream.write((const char*)&value, 1);
		}

		inline void Write(const String& value)
		{
			m_Stream.write(value.GetPointer(), value.GetLength());
		}

		inline void WriteLine()
		{
			Write('\n');
		}
		
		inline void WriteLine(const String& value)
		{
			m_Stream.write(value.GetPointer(), value.GetLength());
			Write('\n');
		}

		template <const SizeT LENGTH>
		void Write(const Array<String, LENGTH>& lines)
		{
			for (String line : lines)
			{
				Write(line);
				WriteLine();
			}
		}

		void Write(const DynamicArray<String>& lines)
		{
			for (String line : lines)
			{
				Write(line);
				WriteLine();
			}
		}

		TextFile& operator<<(char value)
		{
			Write(value);
			return *this;
		}

		TextFile& operator<<(const String& value)
		{
			Write(value);
			return *this;
		}

		template <const SizeT LENGTH>
		TextFile& operator<<(const Array<String, LENGTH>& lines)
		{
			Write<LENGTH>(lines);
			return *this;
		}

		TextFile& operator<<(const DynamicArray<String>& lines)
		{
			Write(lines);
			return *this;
		}
	};
}