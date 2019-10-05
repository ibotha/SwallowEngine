#pragma once

#include "Core.hpp"

#include "Window.hpp"
#include "LayerStack.hpp"
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

#include "ImGui/ImGuiLayer.hpp"

#include "Renderer/Shader.hpp"
#include "Renderer/Buffer.hpp"
#include "Renderer/VertexArray.hpp"

#include "Swallow/Core/Timestep.hpp"

namespace Swallow {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event &e);

		void PushLayer(Ref<Layer> layer);
		void PushOverlay(Ref<Layer> layer);
		void PopLayer(Ref<Layer> layer);
		void PopOverlay(Ref<Layer> layer);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		inline void End() { m_Running = false; }
	private:
		bool OnWindowClose(WindowCloseEvent &e);
		bool OnWindowResize(WindowResizeEvent &e);

		Scope<Window> m_Window;
		Ref<ImGuiLayer> m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimised = false;
		LayerStack m_LayerStack;

		static Application* s_Instance;
		float m_LastFrameTime = 0.0f;
	};

	Application *CreateApplication();

}