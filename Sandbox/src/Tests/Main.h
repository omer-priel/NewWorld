#include <NewWorld.h>
#include <NewWorld/Math/Vector2.h>

#include "Group.h"

namespace Sandbox::Tests
{

	void TestCore()
	{
		DEBUG("IDs: ", NewWorld::DataTypes::Build::c_LastTypeId);
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
			INFO(world);
		}
	}

	void Test2()
	{
		using namespace NewWorld;

		Debug::Logger logger("Tests");

		logger.Info("Loggers Count: ", Debug::Logger::GetLoggersCount());

		for (uint i = 0; i < 5; i++)
		{
			logger.Critical("------------------------------------------");

			Debug::Logger::SetGeneralShowLevel((Debug::LogLevel)i);

			logger.Critical(i);

			logger.Critical("my name ", "is not ", "for ", 35, " dolars");
			logger.Error("my name ", "is not ", "for ", 35, " dolars");
			logger.Warn("my name ", "is not ", "for ", 35, " dolars");
			logger.Info("my name ", "is not ", "for ", 35, " dolars");
			logger.Debug("my name ", "is not ", "for ", 35, " dolars");

			logger.Critical("------------------------------------------");
		}

		INFO(logger.GetType().GetStaticID());
	}

	void TestsRoot()
	{
		TestCore();

		Test2();

		system("pause");
	}
}