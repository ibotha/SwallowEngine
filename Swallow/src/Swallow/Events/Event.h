#pragma once

#include "Swallow/Core.h"

namespace Swallow
{
	enum class EventType {
		none = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCatagory {
		EventCatagoryApplication	= BIT(0),
		EventCatagoryInput			= BIT(1),
		EventCatagoryKeyboard		= BIT(2),
		EventCatagoryMouse			= BIT(3),
		EventCatagoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATAGORY(catagory) virtual int GetCatagoryFlags() const override { return catagory; }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCatagoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); };

		inline bool IsInCatagory(EventCatagory catagory)
		{
			return GetCatagoryFlags() & catagory;
		}
		bool Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream &os, const Event& e)
	{
		return os << e.ToString();
	}
}