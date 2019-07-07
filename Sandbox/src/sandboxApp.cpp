#include <Swallow.h>
#include "imgui.h"
#include "gtx/transform.hpp"

class StartLayer : public Swallow::Layer {
private:

	std::shared_ptr<Swallow::VertexArray> m_SquareVA;
	std::shared_ptr<Swallow::Shader> m_SquareShader;

	float m_Y = 0.0f;
	float m_YVelocity = 0.0f;
	bool m_CanJump = true;


	Swallow::OrthographicCamera m_Camera;
public:
	StartLayer()
		:Layer("Start Layer"), m_Camera(Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight() * -2.0f, Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight() * 2.0f, -2, 2, -5, 5)
	{
		m_SquareVA.reset(Swallow::VertexArray::Create());
		
		float squareBuffer[8 * 9] = {
 			-1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, -1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f,  1.0f, 1.0f, 1.0f,
			 1.0f,-1.0f, 1.0f, 0.5f, 0.5f, 0.5f,  1.0f, -1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f, 0.5f, 0.5f, 0.5f, -1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f, 0.5f, 0.5f, 0.5f, -1.0f, 1.0f, -1.0f,
			 1.0f, 1.0f, -1.0f, 0.5f, 0.5f, 0.5f,  1.0f, 1.0f, -1.0f,
			 1.0f,-1.0f, -1.0f, 0.5f, 0.5f, 0.5f,  1.0f, -1.0f, -1.0f,
			-1.0f,-1.0f, -1.0f, 0.5f, 0.5f, 0.5f, -1.0f, -1.0f, -1.0f
		};
		std::shared_ptr<Swallow::VertexBuffer> squareVB;
		squareVB.reset(Swallow::VertexBuffer::Create(squareBuffer, sizeof(squareBuffer)));

		squareVB->SetLayout({
			{ Swallow::ShaderDataType::Float3, "a_Position" },
			{ Swallow::ShaderDataType::Float3, "a_Color" },
			{ Swallow::ShaderDataType::Float3, "a_Normal" },
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndex[3 * 12] = {
			//North 0 1 2 3
			0, 1, 2,
			2, 3, 0,
			//East 1 5 6 2
			1, 5, 6,
			6, 2, 1,
			//South 7 6 5 4
			7, 6, 5,
			5, 4, 7,
			//West 0 3 7 4
			0, 3, 7,
			7, 4, 0,
			//Top 0 4 5 1
			0, 4, 5,
			5, 1, 0,
			//Bottom 7 3 2 6
			7, 3, 2,
			2, 6, 7
		};

		std::shared_ptr<Swallow::IndexBuffer> squareIB;
		squareIB.reset(Swallow::IndexBuffer::Create(squareIndex, sizeof(squareIndex) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string sVertexSrc = R"(
			#version 330 core
			

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec3 a_Color;
			layout(location = 2) in vec3 a_Normal;

			out vec3 v_Color;
			out float v_Light;

			uniform vec3 u_LightDirection = vec3(0, -1, 0);
			uniform mat4 u_ViewProjection;

			void main() {
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
				v_Light = max(0.0, dot(normalize(a_Normal), -normalize(u_LightDirection))) * 0.9 + 0.1;
				v_Color = a_Color;
			}
		)";

		std::string sFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Color;
			in float v_Light;

			void main() {
				color = vec4(v_Color * v_Light, 1.0);
			}
		)";

		m_SquareShader.reset(Swallow::Shader::Create(sVertexSrc, sFragmentSrc));

		Swallow::RenderCommand::SetDepthTest(true);
	}

	void OnEvent(Swallow::Event &e) override {
		Swallow::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(StartLayer::OnMouseButtonPressed));
		dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(StartLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(StartLayer::OnKeyPressed));
	}

	bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
	{
		if (e.GetButton() == SW_MOUSE_BUTTON_1)
		{
			m_Camera.SetPosition({ 0, 0, 0 });
			m_Camera.SetRotation({ 0, 0, 0 });
		}
		return true;
	}

	bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
	{
		static glm::vec2 s_OldMouse = glm::vec2(e.GetX(), e.GetY());
		glm::vec2 newMouse = glm::vec2(e.GetX(), e.GetY());
		m_Camera.SetRotation(glm::vec3({ glm::radians(s_OldMouse.y - newMouse.y) * 0.5, glm::radians(s_OldMouse.x - newMouse.x) * 0.5, 0 }) + m_Camera.GetRotation());
		s_OldMouse = glm::vec2(e.GetX(), e.GetY());
		return true;
	}

	bool OnKeyPressed(Swallow::KeyPressedEvent &e)
	{
		if (e.GetKeyCode() == SW_KEY_SPACE && m_CanJump)
		{
			m_YVelocity = 0.15f;
			m_CanJump = false;
		}
		return true;
	}

	virtual void OnImGuiRender() override {
	}

	void OnUpdate() {
		m_YVelocity -= 0.005f;

		if (m_YVelocity + m_Camera.GetPosition().y < 0)
		{
			m_YVelocity = 0.0f;
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0, -m_Camera.GetPosition().y, 0));
			m_CanJump = true;
		}

		m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0, m_YVelocity, 0));
		if (Swallow::Input::IsKeyPressed(SW_KEY_W))
		{
			glm::vec4 t(m_Camera.GetPosition(), 1);
			t += (glm::vec4(0, 0, -0.1, 1) * m_Camera.GetRotationMatrix());
			m_Camera.SetPosition({ t.x, m_Camera.GetPosition().y, t.z });
		}
		if (Swallow::Input::IsKeyPressed(SW_KEY_S))
		{
			glm::vec4 t(m_Camera.GetPosition(), 1);
			t += (glm::vec4(0, 0, 0.1, 1) * m_Camera.GetRotationMatrix());
			m_Camera.SetPosition({ t.x, m_Camera.GetPosition().y, t.z });
		}
		if (Swallow::Input::IsKeyPressed(SW_KEY_A))
		{
			glm::vec4 t(m_Camera.GetPosition(), 1);
			t += (glm::vec4(-0.1, 0, 0, 1) * m_Camera.GetRotationMatrix());
			m_Camera.SetPosition({ t.x, m_Camera.GetPosition().y, t.z });
		}
		if (Swallow::Input::IsKeyPressed(SW_KEY_D))
		{
			glm::vec4 t(m_Camera.GetPosition(), 1);
			t += (glm::vec4(0.1, 0, 0, 1) * m_Camera.GetRotationMatrix());
			m_Camera.SetPosition({ t.x, m_Camera.GetPosition().y, t.z });
		}
		m_Camera.Recalculate();

		Swallow::Renderer::BeginScene(m_Camera);

		Swallow::Renderer::Submit(m_SquareShader, m_SquareVA);

		Swallow::Renderer::EndScene();
	}
};

class Sandbox : public Swallow::Application
{
public:
	Sandbox() {
		PushLayer(new StartLayer());
	}

	~Sandbox() {

	}

private:

};


Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}