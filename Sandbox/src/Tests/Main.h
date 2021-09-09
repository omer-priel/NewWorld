#include <NewWorld.h>

#include <memory>

namespace Sandbox::Tests
{
	class Example : public NewWorld::Object
	{
	NW_CLASS(Example, Tests)

		// Members
	public:
		NewWorld::String m_Name;
		NewWorld::uint m_Age;

	public:
		Example(const char* name, NewWorld::uint age)
			: m_Name(name), m_Age(age)
		{
			DEBUG(m_Name, " created");
		}

		Example(Example& obj)
			: m_Name(obj.m_Name), m_Age(obj.m_Age)
		{
			DEBUG(m_Name, " coped");
		}

		~Example()
		{
			DEBUG(m_Name, " destroyed");
		}

		// Actions
	public:
		void Print()
		{
			DEBUG("{ Name: ", m_Name, ", Age: ", m_Age, " }");
		}
	};

	class Example2 : public Example
	{
	NW_CLASS(Example2, Tests)

	public:
		Example2(const char* name, NewWorld::uint age)
			: Example(name, age)
		{

		}

		// Override
	public:
		virtual NewWorld::String ToString() const override
		{
			return "Example2";
		}
	};

	void TestsRoot()
	{
		using namespace NewWorld::DataTypes::Memory;
		
		{
			ScopePointer<Example> scopePointer("scopePointer", 21);
			IPointer<Example>& ptr = scopePointer;

			INFO(scopePointer);
			INFO(ptr.GetType());

			INFO(*scopePointer);

			Example value = *scopePointer;
			INFO(value);

			scopePointer->m_Age += 10;

			INFO(*scopePointer);
			scopePointer->Print();
		}

		INFO("--------------------");

		{
			SharedPointer<Example> sharedPointer("sharedPointer", 22);
			IPointer<Example>& ptr = sharedPointer;

			INFO(sharedPointer);
			INFO(ptr.GetType());

			INFO(*sharedPointer);

			SharedPointer<Example> sharedPointerCopy = sharedPointer;

			Example value = *sharedPointerCopy;
			INFO(value);

			Example& refValue = *sharedPointerCopy;
			INFO(refValue);

			sharedPointerCopy->m_Age += 10;

			INFO(*sharedPointer);
			sharedPointer->Print();
			INFO(*sharedPointerCopy);
			sharedPointerCopy->Print();
		}

		system("pause");
	}
}