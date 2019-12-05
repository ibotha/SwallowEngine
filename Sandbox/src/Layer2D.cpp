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
	ImGui::ColorEdit4("Colour", glm::value_ptr(col));
	ImGui::InputInt("Quad Amount", &limit);
	ImGui::End();
}

void Layer2D::OnAttach()
{
	Swallow::Renderer2D::Init();
}

void Layer2D::OnDetach()
{
	Swallow::Renderer2D::Shutdown();
}

void Layer2D::OnUpdate(Swallow::Timestep ts)
{
	m_Camera.OnUpdate(ts);

	Swallow::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Swallow::RenderCommand::Clear();

	Swallow::Renderer2D::BeginScene(m_Camera.GetCamera());

	for (int x = 0; x < limit; x++)
		for (int y = 0; y < limit; y++)
			Swallow::Renderer2D::DrawQuad({x, y}, { 0.9f, 0.9f }, col, x);

	Swallow::Renderer2D::EndScene();
}
