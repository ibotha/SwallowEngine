#include "Layer2D.hpp"
#include "gtx/transform.hpp"
#include <gtc/type_ptr.hpp>
#include <imgui.h>
#define AR (Swallow::Application::Get().GetWindow().GetWidth() / static_cast<float>(Swallow::Application::Get().GetWindow().GetHeight()))


Layer2D::Layer2D()
	:m_Camera(-1 * AR, 1 * AR, -1, 1)
{
	m_Camera.SetPosition(glm::vec3(0.0f));
	m_Camera.SetRotation(glm::vec3(0.0f));
	m_Camera.Recalculate();
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
	m_SLib.Load("assets/Shaders/Texture.glsl");
	m_SLib.Load("assets/Shaders/Flatcolour.glsl");
	m_CheckerBoardTexture = Swallow::Texture2D::Create("assets/Textures/Checkerboard.png");
}

bool Layer2D::OnWindowResize(Swallow::WindowResizeEvent & e)
{
	float ar = e.GetWidth() / static_cast<float>(e.GetHeight());
	m_Camera.SetProjectionMatrix(-1 * ar, 1 * ar, 1, 1);
	m_Camera.Recalculate();
	return false;
}

void Layer2D::OnEvent(Swallow::Event & e)
{
	Swallow::EventDispatcher d(e);
	d.Dispatch<Swallow::WindowResizeEvent>(BIND_EVENT_FN(Layer2D::OnWindowResize));
}

void Layer2D::OnImGuiRender()
{
	ImGui::Begin("Props");
	ImGui::SliderFloat4("Colour", glm::value_ptr(col), 0, 1);
	ImGui::End();
}

void Layer2D::OnUpdate(Swallow::Timestep ts)
{
	Swallow::Renderer::BeginScene(m_Camera);
	Swallow::Ref<Swallow::OpenGLShader> &t = std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_SLib.Get("Texture"));
	Swallow::Ref<Swallow::OpenGLShader> &fc = std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_SLib.Get("Flatcolour"));
	m_CheckerBoardTexture->Bind(0);
	t->Bind();
	t->UploadUniformInt1("u_Texture", glm::ivec1(0));
	Swallow::Renderer::Submit(t, m_SquareVA);
	fc->Bind();
	fc->UploadUniformFloat4("u_Colour", col);
	Swallow::Renderer::Submit(fc, m_SquareVA, glm::translate(glm::vec3(0.0f, 0.0f, 0.1f)));
	Swallow::Renderer::EndScene();
}
