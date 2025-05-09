#pragma once

#include"Core.h"
#include"Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"
#include"Window.h"

namespace GameEngine {
	class GE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//TO be defined in sandbox
	Application* CreateApplication();
}