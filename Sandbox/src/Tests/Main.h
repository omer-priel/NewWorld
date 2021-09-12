#include <NewWorld.h>

#include <memory>

namespace Sandbox::Tests
{
	class Example : public NewWorld::Object
	{
	NW_CLASS(Example, Tests)

		// Members
	public:
		//NewWorld::String m_Name;
		const char* m_Name;
		NewWorld::uint m_Age;

	public:
		Example()
			: m_Name("default"), m_Age(13)
		{
			
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

		~Example()
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

	void TestsRoot()
	{
		using namespace NewWorld;

		{
			DynamicArray<Example>arr;
			Example& cell = arr.Emplace("arr 0", 22);
			cell.Print();
			arr[0].Print();
			arr.Emplace("arr 1", 23);
			arr[1].Print();
			arr.Emplace("arr 2", 23);
			arr[2].Print();
			arr.Emplace("arr 3", 23);
			arr[3].Print();
			arr.Emplace("arr 4", 23);
			arr[4].Print();
			arr.Push(Example("arr 5", 24));
			arr[5].Print();
		}

		system("pause");
	}
}