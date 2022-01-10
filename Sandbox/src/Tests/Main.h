#include <NewWorld.h>
#include <NewWorld/Math/Vector2.h>

#include "Settings.h"
#include "Group.h"

namespace Sandbox::Tests
{	
	void TestCore()
	{
		DEBUG(TESTS_LOGGER, "IDs: {}", NewWorld::DataTypes::Build::c_LastTypeId);
		DEBUG(TESTS_LOGGER, "Root Directory: {}", NewWorld::Files::FileManger::GetLogsDirectory());
	}

	void Test1()
	{
		using namespace NewWorld;

		{
			SharedPointer<Group> world("World");
			
			SharedPointer<Entity> user("User", 0.0f, 0.0f, 0.0f);

			SharedPointer<Group> enemies("Enemies");

			SharedPointer<Group> wolfs("Wolfs");
			for (uint i = 0; i < 5; i++)
			{
				SharedPointer<Entity> wolf(String("Wolf_") + std::to_string(i).c_str(), 1.0f, 1.0f, (float)i);
				wolfs->AddEntity(wolf);
			}

			SharedPointer<Group> robbers("Robbers");
			for (uint i = 0; i < 10; i++)
			{
				SharedPointer<Entity> robber(String("Robber_") + std::to_string(i).c_str(), 2.0f, 1.0f, (float)i);
				robbers->AddEntity(robber);
			}

			for (uint i = 1; i < robbers->m_Entitys.size(); i += 2)
			{
				robbers->m_Entitys[i]->m_Location += Vector3(0.5f, 0, 10.5f);
			}

			SharedPointer<Entity> boss("Boss", 3.0f, 1.0f, 0.0f);
						
			enemies->AddEntity(boss);
			enemies->AddSubGroup(wolfs);
			enemies->AddSubGroup(robbers);

			world->AddEntity(user);
			world->AddSubGroup(enemies);

			world->Print();
			INFO(TESTS_LOGGER, world);
		}
	}
	
	void Test2()
	{
		using namespace NewWorld;

		DEBUG(TESTS_LOGGER, "This debug log");
	}
	
	void TestsRoot()
	{
		TestCore();

		Test1();
		Test2();

		ERROR(MAIN_LOGGER, "Press any key to continue . . .");
		std::cin.get();
	}
}