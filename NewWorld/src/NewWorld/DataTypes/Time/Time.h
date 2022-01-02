#pragma once

#include "NewWorld/DataTypes/Object.h"

namespace NewWorld::DataTypes::Time
{
	class Time : public Object
	{
	NW_CLASS(NewWorld::DataTypes::Time, Time)

		// Static
	public:

		// Members
	private:
		uint m_Ticks;
		//m_Hour m_Minute m_Second;

	public:
		Time()
			: m_Ticks(0) { }
		
		Time(ushort ticks)
			: m_Ticks(ticks) { }
		
		Time(Byte hour, Byte minute, Byte secound)
			: m_Ticks(hour * 3600 + minute * 60 + secound) { }

		// Getters and Setters
	public:
		inline uint GetTicks() const { return m_Ticks; }

		inline void SetTicks(uint value) { m_Ticks = value; }

		inline Byte GetHour() const { return m_Ticks / 3600; }

		void SetHour(Byte value)
		{
			m_Ticks = (m_Ticks % 3600) + value * 3600;
		}

		inline Byte GetMinute() const { return m_Ticks % 3600 / 60; }

		void SetMinute(Byte value)
		{
			m_Ticks = (m_Ticks - GetMinute()) + value * 60;
		}

		inline Byte GetSecound() const { return m_Ticks % 60; }

		void SetSecound(Byte value)
		{
			m_Ticks = (m_Ticks - GetSecound()) + value;
		}

		void SetTime(Byte hour, Byte minute, Byte secound)
		{
			m_Ticks = hour * 3600 + minute * 60 + secound;
		}

		// Operators
	public:
		operator uint() const { return m_Ticks; }

		Time& operator +=(const Time& other)
		{
			m_Ticks += other.m_Ticks;
			return *this;
		}

		Time operator+(const Time& other) const
		{
			return Time(m_Ticks + other.m_Ticks);
		}

		Time& operator -=(const Time& other)
		{
			m_Ticks += other.m_Ticks;
			return *this;
		}

		Time operator-(const Time& other) const
		{
			return Time(m_Ticks - other.m_Ticks);
		}

		bool operator==(Time& other) const
		{
			return m_Ticks == other.m_Ticks;
		}

		bool operator!=(Time& other) const
		{
			return m_Ticks != other.m_Ticks;
		}

		bool operator<(Time& other) const
		{
			return m_Ticks < other.m_Ticks;
		}

		bool operator<=(Time& other) const
		{
			return m_Ticks <= other.m_Ticks;
		}

		bool operator>(Time& other) const
		{
			return m_Ticks > other.m_Ticks;
		}

		bool operator>=(Time& other) const
		{
			return m_Ticks >= other.m_Ticks;
		}
	};
}

// std::chrono::system_clock