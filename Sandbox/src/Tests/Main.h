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

		for (uint i = 0; i < 10; i++)
		{
			DEBUG(MAIN_LOGGER, i);
			DEBUG(TESTS_LOGGER, i);
			INFO(MAIN_LOGGER, i);
			INFO(TESTS_LOGGER, i);
			WARN(MAIN_LOGGER, i);
			WARN(TESTS_LOGGER, i);
			ERROR(MAIN_LOGGER, i);
			ERROR(TESTS_LOGGER, i);
			CRITICAL(MAIN_LOGGER, i);
			CRITICAL(TESTS_LOGGER, i);
			
			NW_DEBUG(NW_LOGGER_CORE, i);
			NW_DEBUG(NW_LOGGER_GRAPHICS, i);
			NW_INFO(NW_LOGGER_CORE, i);
			NW_INFO(NW_LOGGER_GRAPHICS, i);
			NW_WARN(NW_LOGGER_CORE, i);
			NW_WARN(NW_LOGGER_GRAPHICS, i);
			NW_ERROR(NW_LOGGER_CORE, i);
			NW_ERROR(NW_LOGGER_GRAPHICS, i);
			NW_CRITICAL(NW_LOGGER_CORE, i);
			NW_CRITICAL(NW_LOGGER_GRAPHICS, i);

			DEBUG(MAIN_LOGGER, "-------------------");
		}
	}
	
	void TestsRoot()
	{
		TestCore();

		Test1();
		Test2();

		system("pause");
	}
}