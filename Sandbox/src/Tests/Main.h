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

		String filename = "Sandbox.exe";
		DEBUG(TESTS_LOGGER, "The file {} {}exists.", filename, (Files::File::Exists(Files::FileManger::GetRootDirectory(filename))) ? "" : "not ");

		String logFile = Files::FileManger::GetLogsDirectory("file.log");
		DEBUG(TESTS_LOGGER, "Log File Path: {}", logFile);

		for (uint i = 0; i < 5; i++)
		{
			uint id = Files::FileManger::CreateTemporaryDirectory();
			String textPath = Files::FileManger::GetTemporaryDirectory(id, "data.txt");
			String imagePath = Files::FileManger::GetTemporaryDirectory(id, "icon.png");
			String folderCopedPath = Files::FileManger::GetTemporaryDirectory(id, "clone");

			DEBUG(TESTS_LOGGER, "Text: {}", textPath);
			DEBUG(TESTS_LOGGER, "Image: {}", imagePath);
			DEBUG(TESTS_LOGGER, "Coped: {}", folderCopedPath);
		}
	}

	void Test3()
	{
		using namespace NewWorld;

		String filePath = Files::FileManger::GetRootDirectory("files/file.txt");
		Files::File file(filePath);

		INFO(TESTS_LOGGER, "Size: {}", file.GetSize());

		char tv = (char)file.Read();
		while (!file.IsLastByte())
		{
			INFO(TESTS_LOGGER, "{}", String::ConverToString(tv));
			file += 3;
			tv = (char)file.Read();
		}
	}

	void TestsRoot()
	{
		TestCore();

		Test1();
		Test2();
		Test3();

		// End
		ERROR(MAIN_LOGGER, "Press any key to continue . . .");
		std::cin.get();
	}
}