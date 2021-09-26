#include <NewWorld.h>

#include "Example.h"

namespace Sandbox::Tests
{

#if 0
	void Test1()
	{
		using namespace NewWorld;

		/*{
			Array<SharedPointer<Example>, 5> arr;

			arr[0] = SharedPointer<Example>("so 0", 22);
			arr[1] = SharedPointer<Example>("so 1", 22);
			arr[2] = SharedPointer<Example>("so 2", 22);
			arr[3] = SharedPointer<Example>("so 3", 22);
			arr[4] = SharedPointer<Example>("so 4", 22);
		}*/

		{
			DataTypes::Collections::BasicDynamicArray<Example, SizeT, 3>arr(5);

			arr[0] = Example("so 0", 22);
			arr[1] = Example("so 1", 22);
			arr[2] = Example("so 2", 22);
			arr[3] = Example("so 3", 22);
			arr[4] = Example("so 4", 22);
			arr.Push(Example("Push", 23));
			arr.Push(Example("Push", 23));
			arr.Push(Example("Push", 23));
			arr.Push(Example("Push", 23));
			arr.Push(Example("Push", 23));
			arr[0].Print();
		}

		{
			DataTypes::Collections::BasicDynamicArray<SharedPointer<Example>, SizeT, 3>arr(5);

			arr[0] = SharedPointer<Example>("so 0", 22);
			arr[1] = SharedPointer<Example>("so 1", 22);
			arr[2] = SharedPointer<Example>("so 2", 22);
			arr[3] = SharedPointer<Example>("so 3", 22);
			arr[4] = SharedPointer<Example>("so 4", 22);
			SharedPointer<Example> a("Push", 23);
			arr.Push(a);
			/*arr.Push(SharedPointer<Example>("Push", 23));
			arr.Push(SharedPointer<Example>("Push", 23));
			arr.Push(SharedPointer<Example>("Push", 23));
			arr.Push(SharedPointer<Example>("Push", 23));
			*/
		}
	}

#endif

	void Test2()
	{
		using namespace NewWorld;

		{

		}
	}

	void TestsRoot()
	{
		Test2();

		system("pause");
	}
}