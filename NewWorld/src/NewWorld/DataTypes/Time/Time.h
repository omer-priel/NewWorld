#pragma once

#include "NewWorld/DataTypes/Object.h"

#include <chrono>

namespace NewWorld::DataTypes::Time
{
	class Time : public Object
	{
	NW_CLASS(NewWorld::DataTypes::Time, Time)

		// Static
	public:
		static constexpr uint TICKS_IN_DAY = 24 * 60 * 60 * 1000;
		static constexpr uint TICKS_IN_HOUR = 60 * 60 * 1000;
		static constexpr uint TICKS_IN_MINUTE = 60 * 1000;
		static constexpr uint TICKS_IN_SECOUND = 1000;
		static constexpr uint TICKS_IN_MILLISECOND = 1;

		static Time Now()
		{
			using namespace std::chrono;

			Long millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
			return Time(millisec_since_epoch % TICKS_IN_DAY);
		}

		// Members
	private:
		uint m_Ticks; // Time in millisecond

	public:
		Time()
			: m_Ticks(0) { }
		
		Time(uint ticks)
			: m_Ticks(ticks) { }
		
		Time(Byte hour, Byte minute, Byte secound, ushort millisecond = 0)
			: m_Ticks(hour * TICKS_IN_HOUR + minute * TICKS_IN_MINUTE + secound * TICKS_IN_SECOUND + millisecond) { }

		// Overide
	public:
		String ToString() const override
		{
			return ToString(false);
		}

		String ToString(bool withMillisecond) const
		{
			String hour = String::ConverToString(GetHour());
			String minute = String::ConverToString(GetMinute());
			String secound = String::ConverToString(GetSecound());

			if (hour.GetLength() == 1) {
				hour = "0" + hour;
			}
			if (minute.GetLength() == 1) {
				minute = "0" + minute;
			}
			if (secound.GetLength() == 1) {
				secound = "0" + secound;
			}

			if (withMillisecond)
			{
				String millisecond = String::ConverToString(GetMillisecond());
				if (millisecond.GetLength() == 1) {
					millisecond = "0" + millisecond;
				}

				return String::Format("{}:{}:{}:{}", hour, minute, secound, millisecond);
			}
			else
			{
				return String::Format("{}:{}:{}:{}", hour, minute, secound);
			}
		}

		// Getters and Setters
	public:
		inline uint GetTicks() const { return m_Ticks; }

		inline void SetTicks(uint value) { m_Ticks = value; }

		inline Byte GetHour() const { return m_Ticks / TICKS_IN_HOUR; }

		void SetHour(Byte value)
		{
			m_Ticks -= GetHour() * TICKS_IN_HOUR;
			m_Ticks += value * TICKS_IN_HOUR;
		}

		inline Byte GetMinute() const { return m_Ticks % TICKS_IN_HOUR / TICKS_IN_MINUTE; }
		
		void SetMinute(Byte value)
		{
			m_Ticks -= GetMinute() * TICKS_IN_MINUTE;
			m_Ticks += value * TICKS_IN_MINUTE;
		}

		inline Byte GetSecound() const { return m_Ticks % TICKS_IN_MINUTE / TICKS_IN_SECOUND; }

		void SetSecound(Byte value)
		{
			m_Ticks -= GetMinute() * TICKS_IN_SECOUND;
			m_Ticks += value * TICKS_IN_SECOUND;
		}

		inline ushort GetMillisecond() const { return m_Ticks % TICKS_IN_SECOUND; }

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