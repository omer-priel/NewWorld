#pragma once

#include "NewWorld/Minimal.h"

#include "NewWorld/Files/Directory.h"

#include <filesystem>
#include <fstream>

namespace NewWorld::Files
{
	class File : public Object
	{
	NW_CLASS(NewWorld::Files, File)

		// Static Functions
	public:
		static inline bool Exists(const String& path);

		static bool Delete(const String& path);

		// Members
	protected:
		std::fstream m_Stream;

	public:
		File(const String& path, bool create = false, bool textMode = true, bool readOnly = false)
			: m_Stream()
		{
			auto openMode = ((textMode) ? (std::fstream::in) : (std::fstream::in | std::fstream::binary));
			
			if (!readOnly)
			{
				openMode = openMode | std::fstream::out;

				if (create && !Exists(path))
				{
					String directoryPath = Directory::GetDirectoryOfFile(path);
					Directory::Create(directoryPath);
					

					m_Stream.open(path.GetPointer(), openMode | std::fstream::app);
					m_Stream.put(0);
					m_Stream.close();
				}
			}

			m_Stream.open(path.GetPointer(), openMode);

			SetIndex(0);
		}

		virtual ~File()
		{
			Close();
		}

		// Getters
	public:
		inline bool IsOpened()
		{
			return m_Stream.is_open();
		}

		inline bool IsLastByte()
		{
			return m_Stream.eof();
		}

		inline Long GetIndex()
		{
			m_Stream.clear();
			return m_Stream.tellg();
		}

		Long GetSize();

		// Setters
	public:
		void SetIndex(Long value)
		{
			m_Stream.clear();
			m_Stream.seekg(value, std::ios::beg);
		}

		void operator++();

		void operator++(int);

		void operator+=(Long value);

		void operator--();

		void operator--(int);

		void operator-=(Long value);

		// Actions
	public:
		inline void Close()
		{
			if (!IsOpened())
			{
				m_Stream.close();
			}
		}

		// Read
	public:
		Byte ReadByte();

		template<const SizeT LENGTH>
		void ReadArray(Array<Byte, LENGTH>& buffer)
		{
			m_Stream.read((char*)&buffer, LENGTH);
		}

		Byte ReadByte(Long index);

		template<const SizeT LENGTH>
		void ReadArray(Long index, Array<Byte, LENGTH>& buffer)
		{
			SetIndex(index);
			m_Stream.read((char*)&buffer, LENGTH);
		}

		File& operator>>(Byte& output)
		{
			m_Stream.read((char*)&output, 1);
			return *this;
		}

		// Write
	public:
		void Write(Byte value);

		template<const SizeT LENGTH>
		void WriteArray(const Array<Byte, LENGTH>& buffer)
		{
			m_Stream.write((const char*)&buffer, LENGTH);
		}

		void Write(Long index, Byte value);

		template<const SizeT LENGTH>
		void WriteArray(Long index, const Array<Byte, LENGTH>& buffer)
		{
			SetIndex(index);
			m_Stream.write((const char*)&buffer, LENGTH);
		}

		File& operator<<(Byte value)
		{
			m_Stream.write((const char*)&value, 1);
			return *this;
		}
	};
}