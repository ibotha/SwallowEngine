#pragma once

#include "Swallow/Layer.h"
#include "Swallow/Events/ApplicationEvent.h"
#include "Swallow/Events/MouseEvent.h"
#include "Swallow/Events/KeyEvent.h"

namespace Swallow {
	class SWALLOW_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}