#include "Layer2D.hpp"
#include "gtx/transform.hpp"
#include <gtc/type_ptr.hpp>
#include <imgui.h>
#define AR (Swallow::Application::Get().GetWindow().GetWidth() / static_cast<float>(Swallow::Application::Get().GetWindow().GetHeight()))


Layer2D::Layer2D()
	:Layer("Sandbox2D"), m_Camera(AR)
{
}

bool Layer2D::OnWindowResize(Swallow::WindowResizeEvent & e)
{
	return false;
}

void Layer2D::OnEvent(Swallow::Event & e)
{
	m_Camera.OnEvent(e);
	Swallow::EventDispatcher d(e);
	d.Dispatch<Swallow::WindowResizeEvent>(BIND_EVENT_FN(Layer2D::OnWindowResize));
}

void Layer2D::OnImGuiRender()
{
	ImGui::Begin("Props");
	ImGui::ColorEdit4("Colour", glm::value_ptr(col), 0, 1);
	ImGui::End();
}

void Layer2D::OnAttach()
{
	m_SquareVA = Swallow::VertexArray::Create();
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	Swallow::Ref<Swallow::VertexBuffer> VB = Swallow::VertexBuffer::Create(vertices, sizeof(vertices));
	VB->SetLayout({
		{ Swallow::ShaderDataType::Float3, "a_Position" },
		{ Swallow::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVA->AddVertexBuffer(VB);
	uint32_t Indeces[] = {
		0, 1, 2,
		2, 3, 0
	};
	Swallow::Ref<Swallow::IndexBuffer> IB = Swallow::IndexBuffer::Create(Indeces, 6);
	m_SquareVA->SetIndexBuffer(IB);
	m_Shader = Swallow::Shader::Create("assets/Shaders/Flatcolour.glsl");
}

void Layer2D::OnDetach()
{
}

void Layer2D::OnUpdate(Swallow::Timestep ts)
{
	m_Camera.OnUpdate(ts);
	Swallow::Renderer::BeginScene(m_Camera.GetCamera());

	// TODO: Fix shader API Methods to be non OpenGL Specific
	Swallow::Ref<Swallow::OpenGLShader> &t = std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader);
	t->Bind();
	t->UploadUniformFloat4("u_Colour", col);

	Swallow::Renderer::Submit(t, m_SquareVA);
	Swallow::Renderer::EndScene();
}
