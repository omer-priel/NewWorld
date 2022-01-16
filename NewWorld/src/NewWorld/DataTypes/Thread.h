#pragma once

#include "NewWorld/DataTypes/Object.h"
#include "NewWorld/DataTypes/Function.h"
#include "NewWorld/DataTypes/Memory/RawPointer.h"
#include "NewWorld/DataTypes/Time/Time.h"

#include <thread>

namespace NewWorld::DataTypes
{
	class Thread : public Object
	{
		NW_CLASS(NewWorld::DataTypes, Thread)

		// Sub-Classes
	public:
		using Func = DataTypes::Function<void>;

		// Static Members
	private:
		static uint s_LastID;
		static thread_local uint s_ID;

		// Static
	public:
		static uint GetThisThreadID()
		{
			return s_LastID;
		}
		
		static inline void Sleap(Long milliseconds)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
		}

		static inline void Sleap(const Time::Time& time)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(time.GetTicks()));
		}

	private:
		static void FullFunc(RawPointer<Thread> thread)
		{
			s_ID = thread->m_ID;
			thread->m_Func();
		}

		// Members
	private:
		uint m_ID;
		Func m_Func;
		std::thread m_Value;

	public:
		Thread(Func func)
			: m_ID(0), m_Func(func), m_Value() { }

		// Overide
	public:
		String ToString() const override
		{
			return String::ConverToString(m_ID);
		}

		// Getters
	public:
		inline uint GetID() const { return m_ID; }
		
		inline bool IsAlive() const { return m_ID != 0; }
		
		// Actions
	public:
		void Start()
		{
			s_LastID++;
			m_ID = s_LastID;

			// Start thread
			m_Value = std::thread(FullFunc, this);
		}

		inline void Wait()
		{
			m_Value.join();
		}

		inline void Detach()
		{
			m_Value.detach();
		}
	};
}