#pragma once
#include "GameEngine/Core/Base.h"
#include "GameEngine/Core/Application.h"

#ifdef HZ_PLATFORM_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	GameEngine::Log::Init();

	HZ_PROFILE_BEGIN_SESSION("Startup", "GameEngineProfile-Startup.json");
	auto app = GameEngine::CreateApplication({ argc, argv });
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Runtime", "GameEngineProfile-Runtime.json");
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Shutdown", "GameEngineProfile-Shutdown.json");
	delete app;
	HZ_PROFILE_END_SESSION();
}

#endif