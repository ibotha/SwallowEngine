#include "Layer2D.hpp"
#include "gtx/transform.hpp"
#include <gtc/type_ptr.hpp>
#include <imgui.h>
#define AR (Swallow::Application::Get().GetWindow().GetWidth() / static_cast<float>(Swallow::Application::Get().GetWindow().GetHeight()))

class SpriteRenderer : public Swallow::Component {
public:
	SpriteRenderer(Swallow::Ref<Swallow::SubTexture2D> tex, const glm::vec4& color = {1,1,1,1})
		:Component("SpriteRenderer"), m_Texture(tex), m_Color(color)
	{}

	virtual void Update(const Swallow::Timestep& ts) override {
		Swallow::Renderer2D::DrawQuad(GetEntity()->pos, { GetEntity()->scale.x, GetEntity()->scale.y }, m_Texture, GetEntity()->rotation.z);
	}

private:
	Swallow::Ref<Swallow::SubTexture2D> m_Texture;
	glm::vec4 m_Color;
};

class PlayerMove : public Swallow::Component {
public:
	PlayerMove()
		:Component("MoveRight")
	{}

	virtual void Update(const Swallow::Timestep& ts) override {
		glm::vec3 move = {0,0,0};
		if (Swallow::Input::IsKeyPressed(SW_KEY_LEFT))
			move.x -= 1;
		if (Swallow::Input::IsKeyPressed(SW_KEY_RIGHT))
			move.x += 1;
		if (Swallow::Input::IsKeyPressed(SW_KEY_DOWN))
			move.y -= 1;
		if (Swallow::Input::IsKeyPressed(SW_KEY_UP))
			move.y += 1;
		GetEntity()->pos += move * ts.GetSeconds();
	}
};

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

	auto stats = Swallow::Renderer2D::GetStatistics();
	ImGui::Text("Renderer2D Stats");
	ImGui::Text("Draw Calls %d", stats.DrawCalls);
	ImGui::Text("Quads %d", stats.QuadCount);
	ImGui::Text("Vertices %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Colour", glm::value_ptr(col));
	ImGui::SliderInt("Limit", &limit, 1, 1000);
	ImGui::End();
}

void Layer2D::OnAttach()
{
	texture = Swallow::Texture2D::Create("assets/textures/CheckerBoard.png");
	spriteSheet = Swallow::Texture2D::Create("assets/textures/sprite_sheet.png");
	subtex = Swallow::SubTexture2D::CreateFromTilePallet(spriteSheet, { 1,3 }, { 1,1 }, { 16, 16 }, { 1, 1 });
	e = Swallow::CreateRef<Swallow::Entity>();
	e->AddComponent<SpriteRenderer>(subtex);
	e->AddComponent<PlayerMove>();
}

void Layer2D::OnDetach()
{
	texture.reset();
	spriteSheet.reset();
	subtex.reset();
	e.reset();
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

		Swallow::Renderer2D::ResetStatistics();
		Swallow::Renderer2D::BeginScene(m_Camera.GetCamera());

		static float rot = 0.0f;

		e->Update(ts);

		//for (int x = 0; x < limit; x++)
		//	for (int y = 0; y < limit; y++)
		//		Swallow::Renderer2D::DrawQuad({ x + 6.0f, y + 6.0f }, { 0.9f, 0.9f }, { 1, 1.0f - (float)y / (float)limit, 1.0f - (float)x / (float)limit, 1.0f });
		//Swallow::Renderer2D::DrawQuad({ 0.0f, 1.6f }, { 0.5f, 0.5f }, { 0.0f, 8.0f, 6.0f, 1.0f });
		//Swallow::Renderer2D::DrawQuad({ 0.5f, 0 }, { 1.0f, 2.0f }, col, rot += 0.1f * ts.GetSeconds());
		//Swallow::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, texture, 0.0f, 10.0f);
		Swallow::Renderer2D::DrawQuad({ -5.0f, -10.0f, 0.1f }, { 10.0f, 10.0f }, subtex);

		Swallow::Renderer2D::EndScene();
	}
}
