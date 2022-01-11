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

		if (!file.IsOpened())
		{
			WARN(TESTS_LOGGER, "The file not exists!");
			return;
		}

		SizeT size = file.GetSize();
		INFO(TESTS_LOGGER, "Size: {}", size);

		Array<Byte, 10> arr;
		for (SizeT i = 0; i < size / arr.size()-1; i++)
		{
			file.ReadArray(arr);
			INFO(TESTS_LOGGER, "{}{}{}{}{}{}{}{}{}{}"
				, String::ConverToString((char)arr[0])
				, String::ConverToString((char)arr[1])
				, String::ConverToString((char)arr[2])
				, String::ConverToString((char)arr[3])
				, String::ConverToString((char)arr[4])
				, String::ConverToString((char)arr[5])
				, String::ConverToString((char)arr[6])
				, String::ConverToString((char)arr[7])
				, String::ConverToString((char)arr[8])
				, String::ConverToString((char)arr[9]));
		}

		char tv = (char)file.Read();
		while (!file.IsLastByte())
		{
			INFO(TESTS_LOGGER, "{}", String::ConverToString(tv));
			tv = (char)file.Read();
		}
	}

	void Test4()
	{
		using namespace NewWorld;

		uint id = Files::FileManger::CreateTemporaryDirectory();
		//String filePath = Files::FileManger::GetTemporaryDirectory(id, "output.txt");
		String filePath = Files::FileManger::GetRootDirectory("files/output.txt");
		Files::File file(filePath, true);

		SizeT size = file.GetSize();
		INFO(TESTS_LOGGER, "Size: {}", size);

		for (uint i = 0; i < 10; i++)
		{
			file.Write((int)'A');
			Array<Byte, 9> word({ (int)' ', (int)'a', (int)'n', (int)'d', (int)' ', (int)'t', (int)'h', (int)'i', (int)'s' });
			file.WriteArray(word);

			file.Write((int)'A');
			file.Write((int)'A');
			file.Write((int)'A');

			INFO(TESTS_LOGGER, "Index: {}", file.GetIndex());

			Array<Byte, 3> empty({ (int)' ', (int)' ',(int)'-' });
			//file -= 3;
			//file.WriteArray(empty);
			file.WriteArray(file.GetIndex()-3, empty);

			file.Write((int)'\n');
		}
	}

	void TestsRoot()
	{
		TestCore();

		Test1();
		Test2();
		Test3();
		Test4();

		// End
		ERROR(MAIN_LOGGER, "Press any key to continue . . .");
		std::cin.get();
	}
}