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
		Example()
			: m_Name("default"), m_Age(13)
		{
			
		}


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
			INFO("{ Name: ", m_Name, ", Age: ", m_Age, " }");
		}
	};

	void TestsRoot()
	{
		using namespace NewWorld;
		
		{
			Array<Example, 10> arr;

			for (uint i = 0; i < arr.GetLength(); i++)
			{
				arr[i] = Example((std::string("value ") + (char)('0' + i)).c_str(), 20 + i);
			}

			Example& sp = arr[4];

			for (uint i = 0; i < arr.GetLength(); i++)
			{
				arr[i].Print();
			}

			sp = Example("sp", 23);

			for (uint i = 0; i < arr.GetLength(); i++)
			{
				arr[i].Print();
			}

			arr.Fill("Fill", 23);

			for (uint i = 0; i < arr.GetLength(); i++)
			{
				arr[i].Print();
			}

			INFO(arr.GetType().GetName());
		}

		system("pause");
	}
}