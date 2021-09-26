#include <NewWorld.h>

namespace Sandbox::Tests
{
	class Example : public NewWorld::Object
	{
		NW_CLASS(Example, Tests)

	public:
		using String = NewWorld::String; //const char*;

		// Members
	public:
		String m_Name;
		NewWorld::uint m_Age;

	public:
		Example()
			: m_Name("default"), m_Age(13)
		{
			DEBUG(m_Name, " created");
		}


		Example(const char* name, NewWorld::uint age)
			: m_Name(name), m_Age(age)
		{
			DEBUG(m_Name, " created");
		}

		Example(const Example& obj)
			: m_Name(obj.m_Name), m_Age(obj.m_Age)
		{
			DEBUG(m_Name, " coped");
		}

		virtual ~Example()
		{
			DEBUG(m_Name, " destroyed");
		}

		// Actions
	public:
		void Print()
		{
			INFO("{ Name: ", m_Name, ", Age: ", m_Age, " }");
		}
	};
}