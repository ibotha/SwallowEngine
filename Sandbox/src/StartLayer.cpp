#include "StartLayer.hpp"
#include "Swallow/Renderer/Primatives.hpp"

StartLayer::StartLayer()
	:Layer("Start Layer"), m_Camera(glm::radians(60.0f), Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight(), 0.0001f, 100000.0f)
{
	pos = glm::vec4(0, 0, 0, 0);
	rot = glm::vec4(0, 0, 0, 0);

	m_BoxMaterial = Swallow::FlatColourMaterial::Create();
	m_BoxMaterial->SetColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	m_FloorMaterial = Swallow::FlatColourMaterial::Create();
	m_FloorMaterial->SetColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	m_CheckerBoardTexture = Swallow::Texture2D::Create("assets/textures/CheckerBoard.png");
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
	SW_INFO("HERE");

	m_Text = Swallow::Text::Create();
	std::string hi = R"(
  It is a period of civil war. Rebel spaceships,
   striking from a hidden base, have won their
first victory against the evil Galactic Empire.
During the battle, Rebel spies managed to steal
  secret plans to the Empire's ultimate weapon,
the DEATH STAR, an armored space station with enough
    power to destroy an entire planet. 

 Pursued by the Empire’s sinister agents, Princess
  Leia races home aboard her starship, custodian of
 the stolen plans that can save her people and restore
          freedom to the galaxy...
		  )";
	m_Text->SetText(hi);
	m_Text->SetColour(glm::vec4(0.7, 0.5, 0.1, 1.0));
	m_Text->GetTransform()->SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));
	m_Text->GetTransform()->SetScale(glm::vec3(0.4f, 0.4f, 0.4f));
	m_Text->Recalculate();
	SW_INFO("HERE");
}

void StartLayer::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
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
	static_cast<void>(e); // Silencing unused parameter error
	static_cast<void>(m_Y); // Silencing unused private field error
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

	static float rot = 0.0f;
	rot += 1.0f * ts.GetSeconds();

	m_Text->GetTransform()->SetPosition(glm::vec3(0.0, rot / 3.0 - 5, -2.0));
	m_Text->Recalculate();

	Swallow::Renderer::Submit(m_Cube);
	Swallow::Renderer::Submit(m_Floor);
	Swallow::Renderer::Submit(m_Text);

	Swallow::Renderer::EndScene();
}