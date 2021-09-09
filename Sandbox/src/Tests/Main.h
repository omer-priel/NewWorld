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
			ScopePointer<int> scopePointer(16);
			IPointer* ptr = &scopePointer;

			
			DEBUG(scopePointer);
			DEBUG(ptr->GetType());

			const int& value = scopePointer.GetValue();
			DEBUG(value);
		}

		system("pause");
	}
}