#pragma once

#include "Swallow/Layer.h"
#include "Swallow/Events/ApplicationEvent.h"
#include "Swallow/Events/MouseEvent.h"
#include "Swallow/Events/KeyEvent.h"

namespace Swallow {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}