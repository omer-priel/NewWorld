#include <NewWorld.h>

#include "Example.h"

#include <array>
#include <initializer_list>

namespace Sandbox::Tests
{
	void Test1()
	{
		using namespace NewWorld;

		const String name = "Omer Priel";

		DEBUG(name);

		for (size_t i = 0; i < name.GetLength(); i++)
		{
			DEBUG(name[i]);
		}

		String name2 = "OMER PRIEL";

		DEBUG(name2);

		DEBUG(name == String("Omer Priel"), " ", name == name2, " ", name != name2);

		DEBUG('-' + name + " " + name2 + " " + name + name);

		for (size_t i = 0; i < name2.GetLength(); i++)
		{
			name2[i] = (char)((int)name2[i] - (int)'A' + (int)'a');
		}

		for (size_t i = 0; i < name2.GetLength(); i++)
		{
			DEBUG(name2[i]);
		}
	}

	void TestsRoot()
	{
		Test1();

		system("pause");
	}
}