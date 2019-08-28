#include "swpch.hpp"
#include "Application.hpp"
#include "Input.hpp"
#include "imgui.h"
#include "glm.hpp"
#include "Renderer/Renderer.hpp"
#include "GLFW/glfw3.h"

namespace Swallow {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		SW_CORE_ASSERT(s_Instance == nullptr, "Cannot run more than one application");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverlay(m_ImGuiLayer);
	}


	Application::~Application()
	{
	}

	void Application::PushLayer(Ref<Layer> layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Ref<Layer> layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::PopLayer(Ref<Layer> layer)
	{
		m_LayerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Ref<Layer> layer)
	{
		m_LayerStack.PopOverlay(layer);
	}

	void Application::OnEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		float x = 0.0f;
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();

			for (Ref<Layer> layer : m_LayerStack)
			{
				RenderCommand::ClearDepth();
				layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();

			for (Ref<Layer> layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();
			
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent &e)
	{
		m_Running = false;

		return true;
	}
}
