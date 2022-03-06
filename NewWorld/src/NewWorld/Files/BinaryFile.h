#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Files/File.h"

namespace NewWorld::Files
{
	class BinaryFile : public File
	{
	NW_CLASS(NewWorld::Files, BinaryFile)

	public:
		BinaryFile()
			: File()
		{

		}

		BinaryFile(const String& path, bool create = false, bool readOnly = false)
			: File(path, create, readOnly, false)
		{

		}

		// Actions
	public:
		void Open(const String& path, bool create = false, bool readOnly = false)
		{
			File::Open(path, create, readOnly, false);
		}

		// Read
	public:
		inline void Read(Byte* output, SizeT length)
		{
			m_Stream.read((char*)&output, length);
		}

		inline void Read(Long index, Byte* output, SizeT length)
		{
			SetIndex(index);
			m_Stream.read((char*)&output, length);
		}

		template <typename T>
		inline void Read(T& output)
		{
			m_Stream.read((char*)&output, sizeof(T));
		}

		template <typename T>
		inline void Read(Long index, T& output)
		{
			SetIndex(index);
			m_Stream.read((char*)&output, sizeof(T));
		}

		template <typename T>
		T Read()
		{
			T output;
			Read<T>(output);
			return output;
		}

		template <typename T>
		T Read(Long index)
		{
			T output;
			Read<T>(index, output);
			return output;
		}

		template <typename T>
		BinaryFile& operator>>(T& output)
		{
			m_Stream.read((char*)&output, 1);
			return *this;
		}

		// Write
	public:
		template <typename T>
		inline void Write(const T& value)
		{
			m_Stream.write((const char*)&value, sizeof(T));
		}

		template <typename T>
		inline void Write(Long index, const T& value)
		{
			SetIndex(index);
			m_Stream.write((const char*)&value, sizeof(T));
		}

		template <typename T>
		BinaryFile& operator<<(const T& value)
		{
			m_Stream.write((const char*)&value, sizeof(T));
			return *this;
		}

	};
}