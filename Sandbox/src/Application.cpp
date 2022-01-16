#include <NewWorld.h>
#include <NewWorld/EntryPoint.h>

#include "Settings.h"
#include "Tests/Tests.h"

namespace Sandbox
{
	void PrintMe(const NewWorld::String& msg)
	{
		DEBUG(MAIN_LOGGER, "msg: {}", msg);
	}

	class Application : NewWorld::Application
	{
	NW_CLASS(Sandbox, Application)

	public:
		Application()
		{
			
		}

		void Initialize() override
		{
			NewWorld::DataTypes::Function<void, const NewWorld::String&> func = &PrintMe;
			func("SO");
		}
	};
}

ENTRYPOINT_APPLICATION(Sandbox::Application);