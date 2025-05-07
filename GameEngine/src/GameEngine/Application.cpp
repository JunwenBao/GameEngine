#include "hzpch.h"

#include "Application.h"
#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Log.h"

namespace GameEngine {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		//测试Event
		WindowResizeEvent e(1280, 720);

		//当该事件为Application事件时，响应（正确）
		if (e.IsInCategory(EventCategoryApplication))
		{
			//注意：HZ_TRACE()无法识别WindowResizeEvent变量，因为底层的fmt::format(...)无法识别
			HZ_TRACE(e.ToString()); 
		}
		//当该事件为Input事件时，响应（错误）
		if (e.IsInCategory(EventCategoryInput))
		{
			HZ_TRACE(e.ToString());
		}

		while (true);
	}
}