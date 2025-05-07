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
		//����Event
		WindowResizeEvent e(1280, 720);

		//�����¼�ΪApplication�¼�ʱ����Ӧ����ȷ��
		if (e.IsInCategory(EventCategoryApplication))
		{
			//ע�⣺HZ_TRACE()�޷�ʶ��WindowResizeEvent��������Ϊ�ײ��fmt::format(...)�޷�ʶ��
			HZ_TRACE(e.ToString()); 
		}
		//�����¼�ΪInput�¼�ʱ����Ӧ������
		if (e.IsInCategory(EventCategoryInput))
		{
			HZ_TRACE(e.ToString());
		}

		while (true);
	}
}