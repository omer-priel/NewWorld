#pragma once

#include "NewWorld/DataTypes/Object.h"

#include <string>
#include <format>

namespace NewWorld::DataTypes::Time
{
	class Time : public Object
	{
	NW_CLASS(NewWorld::DataTypes::Time, Time)

		// Static
	public:

		// Members
	private:
		uint m_Ticks; // Time in millisecond

	public:
		Time()
			: m_Ticks(0) { }
		
		Time(uint ticks)
			: m_Ticks(ticks) { }
		
		Time(Byte hour, Byte minute, Byte secound, ushort millisecond = 0)
			: m_Ticks((hour * 3600 + minute * 60 + secound) * 100 + millisecond) { }

		// Overide
	public:
		String ToString() const override
		{
			return String(std::format("{}:{}:{}:{}", GetHour(), GetMinute(), GetSecound(), GetMillisecond()).c_str());
		}

		// Getters and Setters
	public:
		inline uint GetTicks() const { return m_Ticks; }

		inline void SetTicks(uint value) { m_Ticks = value; }

		inline Byte GetHour() const { return (m_Ticks / 100) / 3600; }

		void SetHour(Byte value)
		{
			m_Ticks -= GetHour() * 3600 * 100;
			m_Ticks += value * 3600 * 100;
		}

		inline Byte GetMinute() const { return m_Ticks / (60 * 100) % 60; }
		
		void SetMinute(Byte value)
		{
			m_Ticks -= GetMinute() * 3600 * 100;
			m_Ticks += value * 60 * 100;
		}

		inline Byte GetSecound() const { return m_Ticks / 100 % 60; }

		void SetSecound(Byte value)
		{
			m_Ticks -= GetMinute() * 60 * 100;
			m_Ticks += value * 100;
		}

		inline ushort GetMillisecond() const { return m_Ticks % 100; }

		void SetMillisecon(ushort value)
		{
			m_Ticks = (m_Ticks - GetMillisecond()) + value;
		}

		void SetTime(Byte hour, Byte minute, Byte secound)
		{
			SetTime(hour, minute, secound, 0);
		}

		void SetTime(Byte hour, Byte minute, Byte secound, ushort millisecond)
		{
			m_Ticks = (hour * 3600 + minute * 60 + secound) * 100 + millisecond;
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