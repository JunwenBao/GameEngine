#pragma once

#include "GameEngine/Core.h"

#include <string>
#include <functional>

namespace GameEngine {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	//事件类型
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//使用位标志表示事件
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput		 = BIT(1),
		EventCategoryKeyboard	 = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	//抽象基类：Event，这是所有事件类的基类
	class GE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0; //纯虚函数：子类中必须实现
		virtual const char* GetName() const = 0;	//纯虚函数：子类中必须实现
		virtual int GetCategoryFlags() const = 0;	//纯虚函数：子类中必须实现
		virtual std::string ToString() const { return GetName(); } //虚函数：子类中可重写

		//内联函数：判断事件是否属于指定类别
		//在头文件里定义函数必须加inline，防止"duplicate symbol" 链接错误
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false; //表示事件是否被处理，用于防止重复处理
	};

	//将事件分发给对应的处理器
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}