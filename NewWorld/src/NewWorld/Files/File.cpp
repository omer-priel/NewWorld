#include "nwpch.h"
#include "File.h"

namespace NewWorld::Files
{
	// Static
	bool File::Exists(const String& path)
	{
		return std::filesystem::is_regular_file(path.GetPointer());
	}

	bool File::Delete(const String& path)
	{
		if (Exists(path)) {
			return std::filesystem::remove(path.GetPointer());
		}
		return true;
	}

	// Getters
	Long File::GetSize()
	{
		Long index = GetIndex();

		m_Stream.seekg(0, std::ios::end);
		Long size = m_Stream.tellg();

		m_Stream.seekg(index, std::ios::beg);

		return size;
	}

	// Actions
	void File::operator++()
	{
		m_Stream.seekg(1, std::ios::cur);
	}

	void File::operator++(int)
	{
		m_Stream.seekg(1, std::ios::cur);
	}

	void File::operator+=(Long value)
	{
		m_Stream.seekg(value, std::ios::cur);
	}

	void File::operator--()
	{
		m_Stream.seekg(-1, std::ios::cur);
	}

	void File::operator--(int)
	{
		m_Stream.seekg(1, std::ios::cur);
	}

	void File::operator-=(Long value)
	{
		m_Stream.seekg(0 - value, std::ios::cur);
	}

	// Read
	Byte File::Read()
	{
		Byte ret;
		m_Stream.read((char*)&ret, 1);
		
		return ret;
	}

	Byte File::Read(Long index)
	{
		SetIndex(index);

		Byte ret;
		m_Stream.read((char*)&ret, 1);

		return ret;
	}

	// Write

	void File::Write(Byte value)
	{
		m_Stream.clear();
		m_Stream.write((const char*)&value, 1);
	}

	void File::Write(Long index, Byte value)
	{
		SetIndex(index);

		m_Stream.write((const char*)&value, 1);
	}
}