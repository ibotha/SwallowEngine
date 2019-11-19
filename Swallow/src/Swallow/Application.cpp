#include "swpch.hpp"
#include "Application.hpp"
#include "Input.hpp"
#include "imgui.h"
#include "glm.hpp"
#include "Renderer/Renderer.hpp"
#include "Audio/Audio.hpp"
#include "GLFW/glfw3.h"

namespace Swallow {

	Application* Application::s_Instance = nullptr;

	Application::Application(WindowProps* props)
	{
		SW_CORE_ASSERT(s_Instance == nullptr, "Cannot run more than one application");
		s_Instance = this;

		if (props)
		{
			SW_CORE_INFO("Window made with: {}, {} As {}", props->Width, props->Height, props->Title);
			m_Window = Scope<Window>(Window::Create(*props));
		}
		else
			m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
		Audio::Init();

		m_ImGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::RefreshWindow()
	{
		if (m_Props)
		{
			PopOverlay(m_ImGuiLayer);
			m_Window.reset();
			m_Window = Scope<Window>(Window::Create(*m_Props));
			m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
			Renderer::Init();
			Audio::Init();
			delete m_Props;
			m_Props = nullptr;
			PushOverlay(m_ImGuiLayer);
		}
	}

	void Application::RecreateWindow(WindowProps* props)
	{
		m_Props = new WindowProps();
		*m_Props = *props;
		// Renderer::Init();
		// Audio::Init();
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
		while (m_Running)
		{
			RefreshWindow();
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();

			for (Ref<Layer> layer : m_LayerStack)
			{
				RenderCommand::ClearDepth();
				if (layer)
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
		static_cast<void>(e);
		m_Running = false;

		return true;
	}
}
