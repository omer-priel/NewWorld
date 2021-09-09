#include <NewWorld.h>
#include <memory>

#include <NewWorld/DataTypes/Memory/RawPointer.h>
#include <NewWorld/DataTypes/Memory/ScopePointer.h>
#include <NewWorld/DataTypes/Memory/SharedPointer.h>

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
		INFO("TestsRoot");

		NewWorld::Object obj;

		DEBUG(obj);

		Example example("unit1", 2);

		DEBUG(example);
		example.Print();

		NewWorld::String str = example.ToString();

		DEBUG(str.GetType().GetFullName());

		Example2 example2("unit2", 4);

		DEBUG(example2);
		example2.Print();

		NewWorld::DataTypes::Type type = example2.GetType();

		DEBUG(type.GetType().GetFullName());

		NewWorld::DataTypes::Memory::RawPointer<int> rawPointer = nullptr;
		
		using namespace NewWorld::DataTypes::Memory;

		DEBUG(rawPointer);
		
		{
			ScopePointer<int> scopePointer(55);
			int* p = scopePointer.m_Value;
			IPointer* ptr = &scopePointer;

			
			DEBUG(scopePointer);
			DEBUG(ptr->GetType());

			const int& value = scopePointer.GetValue();
			DEBUG(value);
		}

		std::unique_ptr<int> a;

		system("pause");
	}
}