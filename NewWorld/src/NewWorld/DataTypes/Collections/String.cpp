#include "nwpch.h"
#include "String.h"

#include <algorithm>

namespace NewWorld::DataTypes::Collections
{
	int String::Find(char value, SizeT from) const
	{
		SizeT to = GetLength();
		return Find(value, from, to);
	}

	int String::Find(char value, SizeT from, SizeT to) const
	{
		to = (to < GetLength()) ? to : GetLength() - 1;
		for (SizeT i = from; i <= to; i++)
		{
			if (m_Value[i] == value)
			{
				return i;
			}
		}
		return -1;
	}

	int String::Find(const String& value, SizeT from) const
	{
		SizeT to = GetLength();
		return Find(value, from, to);
	}

	int String::Find(const String& value, SizeT from, SizeT to) const
	{
		to = (to < GetLength()) ? to : GetLength() - 1;
		to -= value.GetLength() - 1;

		for (SizeT i = from; i <= to; i++)
		{
			bool found = m_Value[i] == value[0];
			for (SizeT j = 1; j < value.GetLength() && found; j++)
			{
				found = m_Value[i + j] == value[j];
			}
			if (found)
			{
				return i;
			}
		}
		return -1;
	}

	int String::FindLast(char value, SizeT from) const
	{
		SizeT to = GetLength();
		return FindLast(value, from, to);
	}

	int String::FindLast(char value, SizeT from, SizeT to) const
	{
		to = (to < GetLength()) ? to : GetLength() - 1;
		for (SizeT i = to; i >= from; i--)
		{
			if (m_Value[i] == value)
			{
				return i;
			}
		}
		return -1;
	}

	int String::FindLast(const String& value, SizeT from) const
	{
		SizeT to = GetLength();
		return FindLast(value, from, to);
	}

	int String::FindLast(const String& value, SizeT from, SizeT to) const
	{
		to = (to < GetLength()) ? to : GetLength() - 1;
		from += value.GetLength() - 1;

		for (SizeT i = to; i >= from; i--)
		{
			bool found = m_Value[i] == value[0];
			for (SizeT j = 1; j < value.GetLength() && found; j++)
			{
				found = m_Value[i - j] == value[j];
			}
			if (found)
			{
				return i;
			}
		}
		return -1;
	}

	String String::Substring(SizeT index) const
	{
		return Substring(index, GetLength() - index);
	}

	String String::Substring(SizeT index, SizeT count) const
	{
		if (count == 0 || index >= GetLength())
		{
			return String("");
		}

		char* ret = new char[count + 1];
		std::memcpy(ret, m_Value.c_str() + index, count);
		ret[count] = '\0';

		return String(ret);
	}

	void String::Replace(char oldChar, char newChar)
	{
		std::replace(m_Value.begin(), m_Value.end(), oldChar, newChar);
	}
}