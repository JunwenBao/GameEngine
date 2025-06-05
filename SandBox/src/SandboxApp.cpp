#include <GameEngine.h>
#include <GameEngine/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public GameEngine::Application
{
public:
	Sandbox(GameEngine::ApplicationCommandLineArgs args)
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

GameEngine::Application* GameEngine::CreateApplication(ApplicationCommandLineArgs args)
{
	return new Sandbox(args);
}