#pragma once

#include "hzpch.h"

#include "GameEngine/Core/Core.h"
#include "GameEngine/Events/Event.h"

namespace GameEngine {

	//�ṹ�壺���洰�ڵĻ������ԣ�������+��С��
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "My Game Engine", uint32_t width = 1600, uint32_t height = 900)
			: Title(title), Width(width), Height(height) {}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0; //���麯����ÿ֡����һ�Σ����ڴ��ڵ�ˢ�¡��¼���ѯ

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0; //���û����VSync����ֱͬ���������ڿ���֡���Ƿ�����Ļˢ����ͬ������ֹ����˺��
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}