#include <NewWorld.h>
#include <NewWorld/Math/Vector2.h>

#include "Settings.h"
#include "Group.h"

namespace Sandbox::Tests
{	
	void TestCore()
	{
		DEBUG(MAIN_LOGGER , "IDs: {}", NewWorld::DataTypes::Build::c_LastTypeId);
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
			INFO(TESTS_LOGGER, "{}", world);
		}
	}
	
	void Test2()
	{
		using namespace NewWorld;

		for (uint i = 0; i < 5; i++)
		{
			NW_DEBUG(NW_LOGGER_CORE, i);
			DEBUG(TESTS_LOGGER, i);
			NW_INFO(NW_LOGGER_CORE, i);
			INFO(TESTS_LOGGER, i);
			NW_WARN(NW_LOGGER_CORE, i);
			WARN(TESTS_LOGGER, i);
			NW_ERROR(NW_LOGGER_CORE, i);
			ERROR(TESTS_LOGGER, i);
		}

		Time t1(1, 0, 0);
		Time t2(1, 30, 0);
		Time t3(2, 45, 30);

		ERROR(TESTS_LOGGER, t1);
		ERROR(TESTS_LOGGER, t2);
		ERROR(TESTS_LOGGER, t3);

		ERROR(TESTS_LOGGER, Time::Now());

		short num = -1;
		ushort unum = 1;
		ERROR(TESTS_LOGGER, "{} {}", unum, num);

		int num2 = -1;
		uint unum2 = 1;
		ERROR(TESTS_LOGGER, "{} {}", unum2, num2);

		Vector3 v(1.5f, 1, 331.11145f);
		ERROR(TESTS_LOGGER, "v : {}", v);

		Vector3 v2(1.7, 0, 111.12345f);
		ERROR(TESTS_LOGGER, "v2: {}", v2);
	}
	
	void TestsRoot()
	{
		TestCore();

		Test1();
		Test2();

		system("pause");
	}
}