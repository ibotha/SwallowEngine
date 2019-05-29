#include "swpch.h"
#include "Application.h"
#include "Input.h"
#include "imgui.h"

#include <glad/glad.h>

namespace Swallow {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		SW_CORE_ASSERT(s_Instance == nullptr, "Cannot run more than one application");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 6] = {
			 0.0f, -0.75f,  0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f,
			0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		unsigned int indexes[3] = {
			0, 1, 2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

		std::string vertexSrc = R"(
			#version 330 core
			
			uniform float u_Scale;

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec3 a_Color;

			out vec3 v_Color;

			void main() {
				v_Color = a_Color;
				gl_Position = vec4(a_Position * u_Scale, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_Color;

			void main() {
				
				color = vec4(v_Color, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}


	Application::~Application()
	{
	}

	void Application::PushLayer(Layer * layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer * layer)
	{
		m_LayerStack.PushOverlay(layer);
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
			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
			GLint loc = glGetUniformLocation(m_Shader->getRendererID(), "u_Scale");
			glUniform1f(loc, x);

			float vertices[3 * 6] = {
				 0.0f,  0.75f,  0.0f, 1.0f, 0.0f, 0.0f,
				-0.5f,  -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
				 0.5f,  -0.5f,  0.0f, 0.0f, 0.0f, 1.0f,
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			static bool open = true;
			ImGui::Begin("Test", &open, 0);
			ImGui::SliderFloat("Movement", &x, 0.0f, 1.0f);
			ImGui::End();

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
