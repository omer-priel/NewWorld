#include <NewWorld.h>

#include "Settings.h"
#include "Entity.h"

namespace Sandbox::Tests
{
	class Group : public NewWorld::Object
	{
		NW_CLASS(Sandbox::Tests, Group)
	public:

		// Members
	public:
		NewWorld::String m_Name;
		NewWorld::DynamicArray<NewWorld::SharedPointer<Group>> m_SubGroups;
		NewWorld::DynamicArray<NewWorld::SharedPointer<Entity>> m_Entitys;

	public:
		Group(const NewWorld::String& name)
			: m_Name(name)
		{

		}

		// Actions
	public:
		void AddSubGroup(NewWorld::SharedPointer<Group> group)
		{
			m_SubGroups.push_back(group);
		}

		void AddEntity(NewWorld::SharedPointer<Entity> entity)
		{
			m_Entitys.push_back(entity);
		}

		void Print()
		{
			Print("");
		}

	private:
		void Print(NewWorld::String tabs)
		{
			INFO(tabs, m_Name, ":");
			tabs += "\t";

			for each (NewWorld::SharedPointer<Entity> entity in m_Entitys)
			{
				INFO(tabs, entity);
			}

			for each (NewWorld::SharedPointer<Group> group in m_SubGroups)
			{
				group->Print(tabs);
			}
		}
	};
}