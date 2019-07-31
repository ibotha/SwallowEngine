#include <Swallow.h>
#include "imgui.h"
#include "gtx/transform.hpp"

class StartLayer : public Swallow::Layer {
private:

	std::shared_ptr<Swallow::VertexArray> m_SquareVA;
	std::shared_ptr<Swallow::Shader> m_SquareShader;

	float	m_Y = 0.0f;
	float	m_YVelocity = 0.0f;
	bool	m_CanJump = true;
	glm::vec4 pos;
	glm::vec4 rot;


	Swallow::PerspectiveCamera m_Camera;
public:
	StartLayer()
		:Layer("Start Layer"), m_Camera(glm::radians(60.0f), Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight(), 0.0001f, 100000.0f)
	{
		pos = glm::vec4(0, 0, 0, 0);
		rot = glm::vec4(0, 0, 0, 0);
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

			out vec3 v_Normal;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Rot;
			uniform mat4 u_Model;

			void main() {
				gl_Position = (u_ViewProjection * u_Model) * vec4(a_Position, 1.0);
				v_Normal = normalize(u_Rot * vec4(a_Normal, 0.0)).xyz;
			}
		)";

		std::string sFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Normal;

			uniform vec3 u_LightDirection = vec3(0, -1, 0);
			uniform vec4 u_Color = vec4(0.6, 0.1, 0.5, 1.0);

			void main() {
				float v_Light = max(0.0, dot(v_Normal, -normalize(u_LightDirection))) * 0.9 + 0.1;
				color = vec4(u_Color * v_Light);
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
			pos = glm::vec4(0, 0, 0, 1);
			rot = glm::vec4(0, 0, 0, 1);
		}
		return true;
	}

	bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
	{
		static glm::vec2 s_OldMouse = glm::vec2(e.GetX(), e.GetY());
		glm::vec2 newMouse = glm::vec2(e.GetX(), e.GetY());
		rot += glm::vec4(glm::radians(s_OldMouse.y - newMouse.y) * 0.5,glm::radians(s_OldMouse.x - newMouse.x) * 0.5, 0, 0);
		rot.x = std::clamp(rot.x, -(glm::half_pi<float>() - 0.01f), glm::half_pi<float>() - 0.01f);
		s_OldMouse = glm::vec2(e.GetX(), e.GetY());
		return true;
	}

	bool OnKeyPressed(Swallow::KeyPressedEvent &e)
	{
		return true;
	}

	virtual void OnImGuiRender() override {
	}

	void OnUpdate(Swallow::Timestep ts) {
		
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
		static float rot = 0.0f;
		rot += 1.0f * ts.GetSeconds();
		m_SquareShader->UploadUniform("u_Color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		Swallow::Renderer::Submit(m_SquareShader, m_SquareVA, glm::translate(glm::vec3(4.0, 0.0, 0.0)));
		m_SquareShader->UploadUniform("u_Color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		Swallow::Renderer::Submit(m_SquareShader, m_SquareVA, glm::translate(glm::vec3(0.0, 0.0, 4.0)));
		m_SquareShader->UploadUniform("u_Color", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		m_SquareShader->UploadUniform("u_Rot", glm::rotate(rot, glm::vec3(1, 0, 0)));
		Swallow::Renderer::Submit(m_SquareShader, m_SquareVA, glm::translate(glm::vec3(-4.0, 0.0, 0.0)) * glm::rotate(rot, glm::vec3(1, 0, 0)));
		m_SquareShader->UploadUniform("u_Rot", glm::identity<glm::mat4>());
		m_SquareShader->UploadUniform("u_Color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Swallow::Renderer::Submit(m_SquareShader, m_SquareVA, glm::translate(glm::vec3(0.0, -2.01, -0.0)) * glm::scale(glm::vec3(100, 1, 100)));

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