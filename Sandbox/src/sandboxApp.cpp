#include <Swallow.h>
#include "imgui.h"

class StartLayer : public Swallow::Layer {
private:
	std::shared_ptr<Swallow::VertexArray> m_VertexArray;
	std::shared_ptr<Swallow::Shader> m_Shader;

	std::shared_ptr<Swallow::Shader> m_SquareShader;
	//std::shared_ptr<Swallow::VertexArray> m_SquareVA;

	Swallow::Camera c;
	std::shared_ptr<Swallow::VertexArray> m_SquareVA;
	bool proj = false;
public:
	StartLayer()
		:Layer("Start Layer"), c({ 0, 0, 0 }, { 0, 0, 3 })
	{
		m_SquareVA.reset(Swallow::VertexArray::Create());
		
		float squareBuffer[4 * 3] = {
			 0.0f, 1.0f,  0.0f,
			 -1.0f,  -1.0f,  -1.0f,
			 0.0f,  -1.0f,  1.0f,
			 1.0f,  -1.0f,  -1.0f
		};
		c.SetPerspectiveProjection(glm::radians(45.0f), 1, 0.1, 1000);
		std::shared_ptr<Swallow::VertexBuffer> squareVB;
		squareVB.reset(Swallow::VertexBuffer::Create(squareBuffer, sizeof(squareBuffer)));

		squareVB->SetLayout({
			{ Swallow::ShaderDataType::Float3, "a_Position" },
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndex[2 * 3] = {
			0, 1, 2,
			2, 3, 0
		};
		std::shared_ptr<Swallow::IndexBuffer> squareIB;
		squareIB.reset(Swallow::IndexBuffer::Create(squareIndex, sizeof(squareIndex) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string sVertexSrc = R"(
			#version 330 core
			
			uniform vec3 u_Position;
			uniform mat4 u_Camera;

			layout(location = 0) in vec3 a_Position;
			out float m_Light;

			void main() {
				gl_Position = u_Camera * vec4(u_Position + a_Position, 1.0);
				m_Light = dot(a_Position, vec3(0, 1, 0));
			}
		)";

		std::string sFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in float m_Light;

			void main() {
				color = vec4(0.2, 0.2, 0.8, 1.0) * m_Light;
			}
		)";

		m_SquareShader.reset(Swallow::Shader::Create(sVertexSrc, sFragmentSrc));
	}

	void OnEvent(Swallow::Event &e) override {
		Swallow::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(StartLayer::OnMouseButtonPressed));
	}

	bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
	{
		if (e.GetButton() == SW_MOUSE_BUTTON_1)
		{
			c.SetPosition({ 0, 0, 0 });
			c.SetRotation({ 0, 0, 0 });
		}
		return true;
	}

	virtual void OnImGuiRender() override {
	}

	void OnUpdate() {

		if (Swallow::Input::IsKeyPressed(SW_KEY_W))
		{
			glm::vec4 t(c.GetPosition(), 1);
			t += (glm::vec4(0, 0, -0.1, 1) * c.GetRotationMatrix());
			c.SetPosition({ t.x, t.y, t.z });
		}
		if (Swallow::Input::IsKeyPressed(SW_KEY_S))
		{
			glm::vec4 t(c.GetPosition(), 1);
			t += (glm::vec4(0, 0, 0.1, 1) * c.GetRotationMatrix());
			c.SetPosition({ t.x, t.y, t.z });
		}
		if (Swallow::Input::IsKeyPressed(SW_KEY_A))
		{
			glm::vec4 t(c.GetPosition(), 1);
			t += (glm::vec4(-0.1, 0, 0, 1) * c.GetRotationMatrix());
			c.SetPosition({ t.x, t.y, t.z });
		}
		if (Swallow::Input::IsKeyPressed(SW_KEY_D))
		{
			glm::vec4 t(c.GetPosition(), 1);
			t += (glm::vec4(0.1, 0, 0, 1) * c.GetRotationMatrix());
			c.SetPosition({ t.x, t.y, t.z });
		}
		if (Swallow::Input::IsKeyPressed(SW_KEY_KP_4))
		{
			c.SetRotation(glm::vec3({ 0, glm::radians(-1.0f), 0 }) + c.GetRotation());
		}
		if (Swallow::Input::IsKeyPressed(SW_KEY_KP_6))
		{
			c.SetRotation(glm::vec3({ 0, glm::radians(1.0f), 0 }) + c.GetRotation());
		}
		if (Swallow::Input::IsKeyPressed(SW_KEY_KP_5))
		{
			if (proj)
				c.SetPerspectiveProjection(glm::radians(45.0f), 1, 0.1, 1000);
			else
				c.SetOrthographicProjection(-10, 10, -10, 10, -10, 10);
			proj = !proj;
		}
		c.Calculate();

		Swallow::Renderer::BeginScene(c);
		m_SquareShader->UploadUniform("u_Camera", c.GetCameraMatrix());

		m_SquareShader->Bind();
		m_SquareShader->UploadUniform("u_Position", glm::vec3({ 0, 0, -5.0f }));
		Swallow::Renderer::Submit(m_SquareVA);
		m_SquareShader->UploadUniform("u_Position", glm::vec3({ 5, 0, 0.0f }));
		Swallow::Renderer::Submit(m_SquareVA);
		m_SquareShader->UploadUniform("u_Position", glm::vec3({ 5, 0, -5.0f }));
		Swallow::Renderer::Submit(m_SquareVA);

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