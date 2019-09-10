#include "StartLayer.hpp"
#include "Swallow/AssetManager/GameObject.hpp"
#include "Swallow/AssetManager/AssetManager.hpp"

StartLayer::StartLayer()
	:Layer("Start Layer"), m_Camera(glm::radians(60.0f), Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight(), 0.0001f, 100000.0f)
{
	pos = glm::vec4(0, 0, 0, 0);
	rot = glm::vec4(0, 0, 0, 0);

	std::string textureVertexSrc = R"(
		#version 330 core
		

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec3 a_Normal;
		layout(location = 2) in vec2 a_TexCoord;

		out vec3 v_Normal;
		out vec2 v_TexCoord;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Rot;
		uniform mat4 u_Model;

		void main() {
			gl_Position = (u_ViewProjection * u_Model) * vec4(a_Position, 1.0);
			v_Normal = normalize(u_Rot * vec4(a_Normal, 0.0)).xyz;
			v_TexCoord = a_TexCoord;
		}
	)";

	std::string textureFragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;
		in vec3 v_Normal;
		in vec2 v_TexCoord;

		uniform vec3 u_LightDirection = vec3(0, -1, 0);
		uniform sampler2D u_Texture;

		void main() {
			float Light = max(0.0, dot(v_Normal, -normalize(u_LightDirection))) * 0.9 + 0.1;
			color = vec4(texture(u_Texture, v_TexCoord).rgb * Light, 1.0);
		}
	)";

	m_BoxMaterial = Swallow::FlatColourMaterial::Create();
	m_BoxMaterial->SetColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Swallow::Ref<Swallow::FlatColourMaterialInstance> SkullMaterial = Swallow::FlatColourMaterial::Create();
	SkullMaterial->SetColour(glm::vec4(0.8f, 0.8f, 1.0f, 1.0f));
	m_FloorMaterial = Swallow::FlatColourMaterial::Create();
	m_FloorMaterial->SetColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//m_CheckerBoardTexture = Swallow::Texture2D::Create("assets/textures/CheckerBoard.png");
	m_Cube = Swallow::Primatives::Cube();
	m_Cube->SetMaterial(m_BoxMaterial);
	m_Cube->GetTransform()->SetPosition(glm::vec3(0.0, -2.01, -0.0));
	m_Cube->GetTransform()->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	m_Cube->GetTransform()->Recalculate();

	m_Floor = Swallow::Primatives::Cube();
	m_Floor->SetMaterial(m_FloorMaterial);
	m_Floor->GetTransform()->SetPosition(glm::vec3(0.0, -0.01, -2.0));
	m_Floor->GetTransform()->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	m_Floor->GetTransform()->Recalculate();

	//Load objects (testing framework beta 0.0.01 alpha beta)
	m_skull = std::make_shared<Swallow::GameObject>();
	m_skull->SetMaterial(SkullMaterial);
	m_skull->GetTransform()->SetPosition(glm::vec3(0, -1, 0));
	m_skull->GetTransform()->SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	m_skull->GetTransform()->SetRotation(glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f));
	m_skull->SetVertexArray(Swallow::AssetManager::FetchObject("Skull", "skull"));
	m_skull->GetTransform()->Recalculate();

	x = Swallow::AudioBuffer::Create("assets/Sounds/InGameSound.wav");
	s = Swallow::AudioSource::Create();
	s->SetPosition({0.0f, 0.0f, 0.0f});
	s->SetVelocity({0.f, 0.f, 0.f});
	s->SetLooping(true);
	s->Play(x);

}

void StartLayer::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	(void)e;
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(StartLayer::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(StartLayer::OnMouseMovedEvent));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(StartLayer::OnKeyPressed));
}

bool StartLayer::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
	if (e.GetButton() == SW_MOUSE_BUTTON_1)
	{
		pos = glm::vec4(0, 0, 0, 1);
		rot = glm::vec4(0, 0, 0, 1);
	}
	return true;
}

bool StartLayer::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
{
	static glm::vec2 s_OldMouse = glm::vec2(e.GetX(), e.GetY());
	glm::vec2 newMouse = glm::vec2(e.GetX(), e.GetY());
	rot += glm::vec4(glm::radians(s_OldMouse.y - newMouse.y) * 0.5,glm::radians(s_OldMouse.x - newMouse.x) * 0.5, 0, 0);
	rot.x = std::clamp(rot.x, -(glm::half_pi<float>() - 0.01f), glm::half_pi<float>() - 0.01f);
	s_OldMouse = glm::vec2(e.GetX(), e.GetY());
	return true;
}

bool StartLayer::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	(void)e;
	return true;
}

void StartLayer::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("CubeColor", glm::value_ptr(col));
	ImGui::End();
}

void StartLayer::OnUpdate(Swallow::Timestep ts) {
	m_Camera = Swallow::PerspectiveCamera(glm::radians(60.0f), Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight(), 0.0001f, 100000.0f);
	float moveSpeed = 5.0f;

	m_YVelocity -= 16.8f * ts.GetSeconds();

	pos.y += m_YVelocity * ts.GetSeconds();

	if (pos.y < 0)
	{
		m_YVelocity = 0.0f;
		pos.y = 0;
		m_CanJump = true;
	}

	m_Camera.SetPosition({ pos.x, pos.y, pos.z });
	m_Camera.SetRotation({ rot.x, rot.y, rot.z });
	m_Camera.Recalculate();

	if (Swallow::Input::IsKeyPressed(SW_KEY_LEFT_SHIFT))
	{
		moveSpeed = 10.0f;
	}
	if (Swallow::Input::IsKeyPressed(SW_KEY_W))
	{
		glm::vec4 t = glm::vec4(0, 0, -1, 1) * m_Camera.GetRotationMatrix();
		glm::vec4 t2 = glm::normalize(glm::vec4(t.x, 0, t.z, 0));
		t2 *= ts.GetSeconds() * moveSpeed;
		pos += t2;
	}
	if (Swallow::Input::IsKeyPressed(SW_KEY_S))
	{
		glm::vec4 t = glm::vec4(0, 0, 1, 1) * m_Camera.GetRotationMatrix();
		glm::vec4 t2 = glm::normalize(glm::vec4(t.x, 0, t.z, 0));
		t2 *= ts.GetSeconds() * moveSpeed;
		pos += t2;
	}
	if (Swallow::Input::IsKeyPressed(SW_KEY_A))
	{
		glm::vec4 t = glm::vec4(-1, 0, 0, 1) * m_Camera.GetRotationMatrix();
		glm::vec4 t2 = glm::normalize(glm::vec4(t.x, 0, t.z, 0));
		t2 *= ts.GetSeconds() * moveSpeed;
		pos += t2;
	}
	if (Swallow::Input::IsKeyPressed(SW_KEY_D))
	{
		glm::vec4 t = glm::vec4(1, 0, 0, 1) * m_Camera.GetRotationMatrix();
		glm::vec4 t2 = glm::normalize(glm::vec4(t.x, 0, t.z, 0));
		t2 *= ts.GetSeconds() * moveSpeed;
		pos += t2;
	}

	if (Swallow::Input::IsKeyPressed(SW_KEY_SPACE) && m_CanJump)
	{
		m_YVelocity = 10.0f;
		m_CanJump = false;
	}

	Swallow::Renderer::BeginScene(m_Camera);

	//Create a primative

	static float rot = 10.0f;
	rot -= 1.0f * ts.GetSeconds();
	Swallow::AudioCommand::SetPosition(m_Camera.GetPosition());

	Swallow::Renderer::Submit(m_Cube);
	Swallow::Renderer::Submit(m_Floor);
	m_skull->GetTransform()->SetRotation(glm::vec3(rot / 2.0f, rot, 0.0f));
	m_skull->GetTransform()->Recalculate();
	Swallow::Renderer::Submit(m_skull);
	Swallow::Renderer::EndScene();
}