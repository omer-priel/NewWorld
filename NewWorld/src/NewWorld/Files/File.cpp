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
	SizeT File::GetSize()
	{
		m_Stream.clear();

		m_Stream.seekg(0, std::ios::end);
		SizeT size = m_Stream.tellg();

		m_Stream.seekg(m_Index, std::ios::beg);

		return size;
	}

	// Actions
	void File::operator++()
	{
		m_Index++;
		m_Stream.seekg(1, std::ios::cur);
	}

	void File::operator++(int)
	{
		m_Index++;
		m_Stream.seekg(1, std::ios::cur);
	}

	void File::operator+=(SizeT value)
	{
		m_Index += value;
		m_Stream.seekg(value, std::ios::cur);
	}

	void File::operator--()
	{
		m_Index--;
		m_Stream.seekg(-1, std::ios::cur);
	}

	void File::operator--(int)
	{
		m_Index--;
		m_Stream.seekg(1, std::ios::cur);
	}

	void File::operator-=(SizeT value)
	{
		m_Index -= value;
		m_Stream.seekg(0 - value, std::ios::cur);
	}

	// Read
	Byte File::Read()
	{
		Byte ret;
		m_Stream.read((char*)&ret, 1);
		
		return ret;
	}

	Byte File::Read(SizeT index)
	{
		m_Stream.seekg(index, std::ios::beg);

		Byte ret;
		m_Stream.read((char*)&ret, 1);

		return ret;
	}

	// Write

}