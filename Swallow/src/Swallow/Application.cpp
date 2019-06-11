#include "swpch.h"
#include "Application.h"
#include "Input.h"
#include "imgui.h"
#include "glm.hpp"

#include <glad/glad.h>

namespace Swallow {

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Swallow::ShaderDataType::Float:	return GL_FLOAT;
		case Swallow::ShaderDataType::Float2:	return GL_FLOAT;
		case Swallow::ShaderDataType::Float3:	return GL_FLOAT;
		case Swallow::ShaderDataType::Float4:	return GL_FLOAT;
		case Swallow::ShaderDataType::Mat3:		return GL_FLOAT;
		case Swallow::ShaderDataType::Mat4:		return GL_FLOAT;
		case Swallow::ShaderDataType::Int:		return GL_INT;
		case Swallow::ShaderDataType::Int2:		return GL_INT;
		case Swallow::ShaderDataType::Int3:		return GL_INT;
		case Swallow::ShaderDataType::Int4:		return GL_INT;
		case Swallow::ShaderDataType::Bool:		return GL_BOOL;
		default:
			break;
		}
		return 0;
	}

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

		float vertices[3 * 7] = {
			 0.0f, 0.75f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" , true }
			};

			m_VertexBuffer->SetLayout(layout);
		}

		int i = 0;
		for (const auto &e : m_VertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(
				i,
				e.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(e.Type),
				e.Normalized ? GL_TRUE :GL_FALSE,
				m_VertexBuffer->GetLayout().GetStride(),
				(const void *)e.Offset);
			i++;
		}

		uint32_t indices[3] = {
			0, 1, 2
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main() {
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec4 v_Color;

			void main() {
				color = v_Color;
			}
		)";

		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
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

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
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
