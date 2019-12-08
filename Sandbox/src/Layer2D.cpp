#include "Layer2D.hpp"
#include "gtx/transform.hpp"
#include <gtc/type_ptr.hpp>
#include <imgui.h>
#define AR (Swallow::Application::Get().GetWindow().GetWidth() / static_cast<float>(Swallow::Application::Get().GetWindow().GetHeight()))

Layer2D::Layer2D()
	:Layer("Sandbox2D"), m_Camera(AR)
{
}

Layer2D::~Layer2D()
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
	ImGui::ColorEdit4("Colour", glm::value_ptr(col));
	ImGui::InputInt("Quad Amount", &limit);
	ImGui::End();
}

void Layer2D::OnAttach()
{
	Swallow::Renderer2D::Init();
	texture = Swallow::Texture2D::Create("assets/textures/CheckerBoard.png");
}

void Layer2D::OnDetach()
{
	Swallow::Renderer2D::Shutdown();
}

void Layer2D::OnUpdate(Swallow::Timestep ts)
{
	SW_PROFILE_FUNCTION();
	{
		SW_PROFILE_SCOPE("CameraController::OnUpdate");
		m_Camera.OnUpdate(ts);
	}

	{
		SW_PROFILE_SCOPE("RenderPrep");
		Swallow::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Swallow::RenderCommand::Clear();
	}

	{
		SW_PROFILE_SCOPE("RenderDraw");
		Swallow::Renderer2D::BeginScene(m_Camera.GetCamera());

		for (int i = 0; i < limit; i++)
		{
			Swallow::Renderer2D::DrawQuad({ 0.5f, 0 }, { 1.0f, 2.0f }, col);
			Swallow::Renderer2D::DrawQuad({ 0.0f, 1.6f }, { 0.5f, 0.5f }, { 0.0f, 8.0f, 6.0f, 1.0f });
			Swallow::Renderer2D::DrawQuad({ 0, 0 , -0.1f }, { 10.0f, 10.0f }, texture);
		}

		Swallow::Renderer2D::EndScene();
	}
}
