#include<GameEngine.h>

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer()
	{
		m_DebugName = "Example";
	}

	void OnUpdate() override
	{
		HZ_INFO("ExampleLayer::Update");
	}

	void OnEvent(GameEngine::Event& event) override
	{
		HZ_TRACE("{}", event.ToString());
	}
};

class Sandbox : public GameEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox();
}