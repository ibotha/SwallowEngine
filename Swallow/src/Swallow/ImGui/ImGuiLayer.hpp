#pragma once

#include <Swallow/Core/Layer.hpp>
#include <Swallow/Events/ApplicationEvent.hpp>
#include <Swallow/Events/MouseEvent.hpp>
#include <Swallow/Events/KeyEvent.hpp>

namespace Swallow {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		ImGuiLayer(const ImGuiLayer&);
		ImGuiLayer &operator=(const ImGuiLayer&);
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