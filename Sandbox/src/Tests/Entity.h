#include <NewWorld.h>

namespace Sandbox::Tests
{
	static NewWorld::uint s_LastID = 0;
	static bool s_DebugMode = false;

	class Entity : public NewWorld::Object
	{
		NW_CLASS(Entity, Sandbox::Tests)

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
				DEBUG(m_Name, " (", m_ID, ") created");
			}
		}


		Entity(const String& name, NewWorld::Vector3& location)
			: m_ID(s_LastID++), m_Name(name), m_Location(location)
		{
			if (s_DebugMode)
			{
				DEBUG(m_Name, " (", m_ID, ") created");
			}
		}

		Entity(const String& name, float x, float y, float z)
			: m_ID(s_LastID++), m_Name(name), m_Location(NewWorld::Vector3(x, y, z))
		{
			if (s_DebugMode)
			{
				DEBUG(m_Name, " (", m_ID, ") created");
			}
		}

		Entity(const Entity& obj)
			: m_ID(s_LastID++), m_Name(obj.m_Name), m_Location(obj.m_Location)
		{
			if (s_DebugMode)
			{
				DEBUG(m_Name, " (", m_ID, ") coped");
			}
		}

		virtual ~Entity()
		{
			if (s_DebugMode)
			{
				DEBUG(m_Name, " (", m_ID, ") destroyed");
			}
		}

		// Actions
	public:
		void Print()
		{
			INFO("{ ID: ", m_ID, " Name: ", m_Name, ", Location : (", m_Location.x, ", ", m_Location.y, ", ", m_Location.z, ") }");
		}

		// Overide
	public:
		NewWorld::String ToString() const override
		{
			return ("{ Name: " + m_Name + ", Location : (" + std::to_string(m_Location.x).c_str() + ", "
				+ std::to_string(m_Location.y).c_str() + ", " + std::to_string(m_Location.z).c_str() + ") }");
		}
	};
}