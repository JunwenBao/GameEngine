#include <GameEngine.h>
#include <GameEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace GameEngine {

	class GameEngineEditor : public Application
	{
	public:
		GameEngineEditor(ApplicationCommandLineArgs args) : Application("Editor", args)
		{
			PushLayer(new EditorLayer());
		}

		~GameEngineEditor()
		{

		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new GameEngineEditor(args);
	}

}