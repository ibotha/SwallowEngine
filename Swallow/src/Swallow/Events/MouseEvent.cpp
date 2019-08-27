#include "swpch.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"

namespace Swallow
{
	#pragma region MouseMovedEvent
	MouseMovedEvent::MouseMovedEvent(): m_MouseX(0), m_MouseY(0){}
	MouseMovedEvent::MouseMovedEvent(float x, float y)
		: m_MouseX(x), m_MouseY(y) {}
	MouseMovedEvent::MouseMovedEvent(const MouseMovedEvent& cpy)
	{
		if (this != &cpy)
			*this = cpy;
	}
	
	MouseMovedEvent &MouseMovedEvent::operator=(const MouseMovedEvent& rhs)
	{
		if (this != &rhs)
		{
			this->m_MouseX = rhs.m_MouseX;
			this->m_MouseY = rhs.m_MouseY;
		}
		return *this;
	}
	MouseMovedEvent::~MouseMovedEvent(){}

	std::string MouseMovedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}
	#pragma endregion

	#pragma region MouseScrolledEvent
	MouseScrolledEvent::MouseScrolledEvent():m_XOffset(0), m_YOffset(0){}
	MouseScrolledEvent::MouseScrolledEvent(float Xoff, float Yoff)
		: m_XOffset(Xoff), m_YOffset(Yoff) {}
	MouseScrolledEvent::MouseScrolledEvent(const MouseScrolledEvent& cpy)
	{
		if (this != &cpy)
			*this = cpy;
	}
	MouseScrolledEvent &MouseScrolledEvent::operator=(const MouseScrolledEvent& rhs)
	{
		if (this != &rhs)
		{
			this->m_XOffset = rhs.m_XOffset;
			this->m_YOffset = rhs.m_YOffset;
		}
		return *this;
	}

	MouseScrolledEvent::~MouseScrolledEvent(){}

	std::string MouseScrolledEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
		return ss.str();
	}
	#pragma endregion

	#pragma region MouseButtonEvent
	MouseButtonEvent::MouseButtonEvent(int button)
		:m_Button(button) {}

	MouseButtonEvent::MouseButtonEvent()
		:m_Button(-1) {}

	MouseButtonEvent::MouseButtonEvent(const MouseButtonEvent& cpy)
	{
		if (this != &cpy)
			*this = cpy;
	}

	MouseButtonEvent &MouseButtonEvent::operator=(const MouseButtonEvent& rhs)
	{
		if (this != &rhs)
		{
			this->m_Button = rhs.m_Button;
		}
		return *this;
	}
	MouseButtonEvent::~MouseButtonEvent(){}
	#pragma endregion

	#pragma region MouseButtonPressedEvent
	MouseButtonPressedEvent::MouseButtonPressedEvent(int button)
		:MouseButtonEvent(button) {}

	MouseButtonPressedEvent::MouseButtonPressedEvent()
		:MouseButtonEvent(-1) {}

	MouseButtonPressedEvent::MouseButtonPressedEvent(const MouseButtonPressedEvent& cpy)
	{
		if (this != &cpy)
			*this = cpy;
	}

	MouseButtonPressedEvent &MouseButtonPressedEvent::operator=(const MouseButtonPressedEvent& rhs)
	{
		if (this != &rhs)
		{
			this->m_Button = rhs.m_Button;
		}
		return *this;
	}


	std::string MouseButtonPressedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_Button;
		return ss.str();
	}

	MouseButtonPressedEvent::~MouseButtonPressedEvent(){}
	#pragma endregion

	#pragma region MouseButtonReleasedEvent
	MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button)
		:MouseButtonEvent(button) {}

	MouseButtonReleasedEvent::MouseButtonReleasedEvent()
		:MouseButtonEvent(-1) {}

	MouseButtonReleasedEvent::MouseButtonReleasedEvent(const MouseButtonReleasedEvent& cpy)
		:MouseButtonEvent(cpy.m_Button) {}

	MouseButtonReleasedEvent &MouseButtonReleasedEvent::operator=(const MouseButtonReleasedEvent& rhs)
	{
		if (this != &rhs)
			this->m_Button = rhs.m_Button;
		return *this;
	}

	MouseButtonReleasedEvent::~MouseButtonReleasedEvent(){}

	std::string MouseButtonReleasedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_Button;
		return ss.str();
	}
	#pragma endregion
}
