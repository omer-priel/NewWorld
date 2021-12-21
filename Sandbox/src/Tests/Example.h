#include <NewWorld.h>

namespace Sandbox::Tests
{
	static NewWorld::uint s_LastID = 0;

	class Example : public NewWorld::Object
	{
		NW_CLASS(Example, Sandbox::Tests)

	public:
		using String = NewWorld::String; //const char*;

		// Members
	public:
		NewWorld::uint m_ID;
		String m_Name;
		NewWorld::uint m_Age;

	public:
		Example()
			: m_ID(s_LastID++), m_Name("default"), m_Age(13)
		{
			DEBUG(m_Name, " (", m_ID, ") created");
		}


		Example(const char* name, NewWorld::uint age)
			: m_ID(s_LastID++), m_Age(age)
		{
			DEBUG(m_Name, " (", m_ID, ") created");
		}

		Example(const Example& obj)
			: m_ID(s_LastID++), m_Name(obj.m_Name), m_Age(obj.m_Age)
		{
			DEBUG(m_Name, " (", m_ID, ") coped");
		}

		virtual ~Example()
		{
			DEBUG(m_Name, " (", m_ID, ") destroyed");
		}

		// Actions
	public:
		void Print()
		{
			INFO("{ ID: ", m_ID, " Name: ", m_Name, ", Age : ", m_Age, " }");
		}
	};
}