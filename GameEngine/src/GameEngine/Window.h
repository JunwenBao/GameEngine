#pragma once

#include "hzpch.h"

#include "GameEngine/Core.h"
#include "GameEngine/Events/Event.h"

namespace GameEngine {

	//�ṹ�壺���洰�ڵĻ������ԣ�������+��С��
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "My Game Engine", unsigned int width = 1280, unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	// Interface representing a desktop system based Window
	class GE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0; //���麯����ÿ֡����һ�Σ����ڴ��ڵ�ˢ�¡��¼���ѯ

		virtual unsigned int GetWidth() const = 0;  
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0; //���û����VSync����ֱͬ���������ڿ���֡���Ƿ�����Ļˢ����ͬ������ֹ����˺��
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}