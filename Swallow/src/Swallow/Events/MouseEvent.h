#pragma once

#include "Event.h"

#include <sstream>

namespace Swallow
{
	class SWALLOW_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATAGORY(EventCatagoryMouse | EventCatagoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	class SWALLOW_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(int Xoff, int Yoff)
			: m_XOffset(Xoff), m_YOffset(Yoff) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATAGORY(EventCatagoryMouse | EventCatagoryInput)

	private:
		int m_XOffset, m_YOffset;
	};

	class SWALLOW_API MouseButtonEvent : public Event
	{
	public:
		inline int GetButton() const { return m_Button; }
		EVENT_CLASS_CATAGORY(EventCatagoryMouseButton | EventCatagoryMouse | EventCatagoryInput)
	protected:
		MouseButtonEvent(int button)
			:m_Button(button) {}

		int m_Button;
	};

	class SWALLOW_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class SWALLOW_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
