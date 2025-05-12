#pragma once

#include"Core.h"
#include"Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/LayerStack.h"
#include"Window.h"

namespace GameEngine {
	class GE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//TO be defined in sandbox
	Application* CreateApplication();
}