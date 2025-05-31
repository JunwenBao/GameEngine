#pragma once

#include "hzpch.h"

#include "GameEngine/Core/Core.h"
#include "GameEngine/Events/Event.h"

namespace GameEngine {

	//结构体：保存窗口的基本属性（窗口名+大小）
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

		virtual void OnUpdate() = 0; //纯虚函数：每帧调用一次，用于窗口的刷新、事件轮询

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0; //启用或禁用VSync（垂直同步）：用于控制帧率是否与屏幕刷新率同步，防止画面撕裂
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}