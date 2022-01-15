#pragma once

#include "NewWorld/DataTypes/Object.h"
#include "NewWorld/DataTypes/Time/Time.h"

#include <thread>

namespace NewWorld::DataTypes::Threads
{
	class Thread : public Object
	{
	NW_CLASS(NewWorld::DataTypes::Threads, Thread)

		// Static
	public:
		static inline void Sleap(Long milliseconds)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
		}

		static inline void Sleap(const Time::Time& time)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(time.GetTicks()));
		}

		// Members
	private:
		uint m_ID; // Time in millisecond
		std::thread m_Value;

	public:
		Thread()
			: m_ID(0), m_Value() { }

		// Overide
	public:
		String ToString() const override
		{
			return String::ConverToString(m_ID);
		}
	};
}