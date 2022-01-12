#include <NewWorld.h>
#include <NewWorld/Files/BinaryFile.h>
#include <NewWorld/Files/TextFile.h>

#include "Settings.h"
#include "Group.h"

#include <limits>

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

	void TestOnlyRead()
	{
		using namespace NewWorld;

		String filePath = Files::FileManger::GetRootDirectory("files\\read.txt");
		Files::TextFile file(filePath);

		INFO(TESTS_LOGGER, "Test File: {}", filePath);

		if (!file.IsOpened())
		{
			WARN(TESTS_LOGGER, "The file not exists!");
			return;
		}

		SizeT size = file.GetSize();
		DEBUG(TESTS_LOGGER, "Size: {}", size);

		Array<Byte, 10> arr;
		for (SizeT i = 0; i < size / arr.size()-1; i++)
		{
			file.ReadArray(arr);
			DEBUG(TESTS_LOGGER, "{}{}{}{}{}{}{}{}{}{}"
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

		char tv = file.Read();
		while (!file.IsLastByte())
		{
			DEBUG(TESTS_LOGGER, "{}", String::ConverToString(tv));
			tv = file.Read();
		}
	}

	void TestOnlyWrite()
	{
		using namespace NewWorld;

		uint id = Files::FileManger::CreateTemporaryDirectory();
		String filePath = Files::FileManger::GetTemporaryDirectory(id, "output.txt");
		Files::File file(filePath, true);

		INFO(TESTS_LOGGER, "Test File: {}", filePath);

		DEBUG(TESTS_LOGGER, "Size: {}", file.GetSize());

		for (uint i = 0; i < 10; i++)
		{
			file.Write((int)'A');
			Array<Byte, 9> word({ (int)' ', (int)'a', (int)'n', (int)'d', (int)' ', (int)'t', (int)'h', (int)'i', (int)'s' });
			file.WriteArray(word);

			file.Write((int)'A');
			file.Write((int)'A');
			file.Write((int)'A');
			file.Write((int)'A');

			Array<Byte, 4> empty({ (int)' ', (int)' ',(int)'-',(int)'-' });
			file.WriteArray(file.GetIndex()-4, empty);

			Array<Byte, 2> endLine({(int)'|',(int)'|' });
			file -= 4;
			file.WriteArray(endLine);
			file += 2;

			file.Write((int)'\n');
		}

		DEBUG(TESTS_LOGGER, "Size: {}", file.GetSize());
	}

	void TestBinaryFile()
	{
		using namespace NewWorld;

		String filePath = Files::FileManger::GetRootDirectory("files\\binary");
		Files::BinaryFile file(filePath, true);

		INFO(TESTS_LOGGER, "Test File: {}", filePath);

		Long size = file.GetSize();
		DEBUG(TESTS_LOGGER, "Size: {}", size);

		size = 256 + 1;
		Long indexToPrint = 0;
		for (Long i = 0- size; i <= size; i++)
		{
			if (i == -10)
			{
				indexToPrint = file.GetIndex();
			}

			if (false)
			{
				file << ((Byte*)&i)[0];
				file << ((Byte*)&i)[1];
				file << ((Byte*)&i)[2];
				file << ((Byte*)&i)[3];
			}
			else
			{
				file << (int)i;
			}
		}

		size = file.GetIndex() / sizeof(int);

		file.SetIndex(indexToPrint);
		for (Long i = -10; i <= 10; i++)
		{
			DEBUG(TESTS_LOGGER, "Get: {}", file.Read<int>());
		}

		DEBUG(TESTS_LOGGER, "Index: {}", file.GetIndex());

	}

	void TestTextFileRead()
	{
		using namespace NewWorld;

		String filePath = Files::FileManger::GetRootDirectory("files\\other.txt");
		Files::TextFile file(filePath, true);

		INFO(TESTS_LOGGER, "Test File: {}", filePath);

		Long size = file.GetSize();
		DEBUG(TESTS_LOGGER, "Size: {}", size);

		WARN(TESTS_LOGGER, "Stage: ReadLines");

		file.SetIndex(0);
		Array<String, 2> firstLines;
		file >> firstLines;
		DEBUG(TESTS_LOGGER, "{}\n{}", firstLines[0], firstLines[1]);

		WARN(TESTS_LOGGER, "Stage: ReadLine");
		String line;
		while (!file.IsLastByte())
		{
			file >> line;
			DEBUG(TESTS_LOGGER, "{}", line);
		}

		WARN(TESTS_LOGGER, "Stage: ReadAll");

		file.SetIndex(0);
		String text = file.ReadAll();
		DEBUG(TESTS_LOGGER, "{}", text);


		WARN(TESTS_LOGGER, "Stage: ReadAllLines");

		file.SetIndex(0);
		DynamicArray<String> lines = file.ReadAllLines();
		for (String item : lines)
		{
			DEBUG(TESTS_LOGGER, "{}", item);
		}
	}

	void TestTextFileWrite()
	{
		using namespace NewWorld;


		String filePath = Files::FileManger::GetRootDirectory("files\\text.txt");
		Files::File::Delete(filePath);
		Files::TextFile file(filePath, true);

		INFO(TESTS_LOGGER, "Test File: {}", filePath);

		Long size = file.GetSize();
		DEBUG(TESTS_LOGGER, "Size: {}", size);

		file.SetIndex(file.GetSize());

		String chank(1024*50, '.');

		DEBUG(TESTS_LOGGER, "Start");

		file << chank;
	}

	void TestsRoot()
	{
		TestCore();

		Test1();
		Test2();
		
		TestOnlyRead();
		TestOnlyWrite();
		TestBinaryFile();
		TestTextFileRead();
		TestTextFileWrite();

		// End
		ERROR(MAIN_LOGGER, "Press any key to continue . . .");
		std::cin.get();
	}
}