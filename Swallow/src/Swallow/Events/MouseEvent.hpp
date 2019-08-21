#pragma once

#include "Event.hpp"
#include <sstream>
#include <string>

namespace Swallow
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent();
		MouseMovedEvent(float x, float y);
		MouseMovedEvent(const MouseMovedEvent&);
		~MouseMovedEvent();
		MouseMovedEvent &operator=(const MouseMovedEvent&);

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override;

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATAGORY(EventCatagoryMouse | EventCatagoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent();
		~MouseScrolledEvent();
		MouseScrolledEvent(float Xoff, float Yoff);
		MouseScrolledEvent(const MouseScrolledEvent&);
		MouseScrolledEvent &operator=(const MouseScrolledEvent&);

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override;

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATAGORY(EventCatagoryMouse | EventCatagoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int GetButton() const { return m_Button; }
		EVENT_CLASS_CATAGORY(EventCatagoryMouseButton | EventCatagoryMouse | EventCatagoryInput)
	protected:
		MouseButtonEvent();
		MouseButtonEvent(int button);
		MouseButtonEvent(const MouseButtonEvent&);
		MouseButtonEvent &operator=(const MouseButtonEvent&);
		~MouseButtonEvent();

		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent();
		MouseButtonPressedEvent(int button);
		MouseButtonPressedEvent(const MouseButtonPressedEvent&);
		MouseButtonPressedEvent &operator=(const MouseButtonPressedEvent&);
		~MouseButtonPressedEvent();

		std::string ToString() const override;

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent();
		MouseButtonReleasedEvent(int button);
		MouseButtonReleasedEvent(const MouseButtonReleasedEvent&);
		~MouseButtonReleasedEvent();
		MouseButtonReleasedEvent &operator=(const MouseButtonReleasedEvent&);


		std::string ToString() const override;

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
