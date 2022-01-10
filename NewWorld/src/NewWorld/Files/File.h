#pragma once

#include "NewWorld/Minimal.h"

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
		SizeT m_Index = 0; // TODO: Remove this member if not nead it in in the tests.

	public:
		File(const String& path, bool create = false, bool textMode = true)
			: m_Stream(path.GetPointer(), (textMode) ? (std::fstream::in | std::fstream::out) : (std::fstream::in | std::fstream::out | std::fstream::binary))
		{

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

		inline SizeT GetIndex()
		{
			return m_Index;
		}

		SizeT GetSize();

		// Setters
	public:
		void SetIndex(SizeT value)
		{
			m_Index = value;
			m_Stream.seekg(m_Index, std::ios::beg);
		}

		void operator++();

		void operator++(int);

		void operator+=(SizeT value);

		void operator--();

		void operator--(int);

		void operator-=(SizeT value);

		// Actions
	public:
		inline void Close();

		// Read
	public:

		// Write
	public:

	};
}