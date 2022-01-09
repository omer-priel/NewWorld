#include <NewWorld.h>

#include "Settings.h"

namespace Sandbox::Tests
{
	static NewWorld::uint s_LastID = 0;
	static bool s_DebugMode = false;

	class Entity : public NewWorld::Object
	{
		NW_CLASS(Sandbox::Tests, Entity)

	public:
		using String = NewWorld::String; //const char*;

		// Members
	public:
		NewWorld::uint m_ID;
		String m_Name;
		NewWorld::Vector3 m_Location;

	public:
		Entity()
			: m_ID(s_LastID++), m_Name("default"), m_Location()
		{
			if (s_DebugMode)
			{
				DEBUG(MAIN_LOGGER, "{} ({}) created", m_Name, m_ID);
			}
		}


		Entity(const String& name, NewWorld::Vector3& location)
			: m_ID(s_LastID++), m_Name(name), m_Location(location)
		{
			if (s_DebugMode)
			{
				DEBUG(MAIN_LOGGER, "{} ({}) created", m_Name, m_ID);
			}
		}

		Entity(const String& name, float x, float y, float z)
			: m_ID(s_LastID++), m_Name(name), m_Location(NewWorld::Vector3(x, y, z))
		{
			if (s_DebugMode)
			{
				DEBUG(MAIN_LOGGER, "{} ({}) created", m_Name, m_ID);
			}
		}

		Entity(const Entity& obj)
			: m_ID(s_LastID++), m_Name(obj.m_Name), m_Location(obj.m_Location)
		{
			if (s_DebugMode)
			{
				DEBUG(MAIN_LOGGER, "{} ({}) coped", m_Name, m_ID);
			}
		}

		virtual ~Entity()
		{
			if (s_DebugMode)
			{
				DEBUG(MAIN_LOGGER, "{} ({}) destroyed", m_Name, m_ID);
			}
		}

		// Actions
	public:
		void Print()
		{
			INFO(MAIN_LOGGER, "{ ID: {} Name: {}, Location: {} }", m_ID, m_Name, m_Location);
		}

		// Overide
	public:
		NewWorld::String ToString() const override
		{
			return String::Format("{ ID: {} Name: {}, Location: {} }", m_ID, m_Name, m_Location);
		}
	};
}