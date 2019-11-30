#pragma once

#include <Swallow/Core/Core.hpp>

#include <Swallow/Core/Window.hpp>
#include <Swallow/Core/LayerStack.hpp>
#include <Swallow/Events/Event.hpp>
#include <Swallow/Events/ApplicationEvent.hpp>
#include <Swallow/Events/KeyEvent.hpp>
#include <Swallow/Events/MouseEvent.hpp>

#include <Swallow/ImGui/ImGuiLayer.hpp>

#include <Swallow/Renderer/Shader.hpp>
#include <Swallow/Renderer/Buffer.hpp>
#include <Swallow/Renderer/VertexArray.hpp>

#include <Swallow/Core/Timestep.hpp>

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