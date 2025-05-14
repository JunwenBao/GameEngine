#include <GameEngine.h>

#include "ImGui/imgui.h"

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		
	}

	void OnUpdate() override
	{
		HZ_INFO("ExampleLayer::Update");

		if (GameEngine::Input::IsKeyPressed(HZ_KEY_TAB)) HZ_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(GameEngine::Event& event) override
	{
		if (event.GetEventType() == GameEngine::EventType::KeyPressed)
		{
			GameEngine::KeyPressedEvent& e = (GameEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == HZ_KEY_TAB)
				HZ_TRACE("Print key is pressed (event)!");
			HZ_TRACE("{0}", (char)e.GetKeyCode());
		}
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