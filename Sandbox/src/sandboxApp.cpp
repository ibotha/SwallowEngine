#include <Swallow.h>
#include "imgui.h"

class StartLayer : public Swallow::Layer {
private:
	std::shared_ptr<Swallow::VertexArray> m_VertexArray;
	std::shared_ptr<Swallow::Shader> m_Shader;

	std::shared_ptr<Swallow::Shader> m_SquareShader;
	//std::shared_ptr<Swallow::VertexArray> m_SquareVA;

	float x, y, xv, yv;
public:
	StartLayer() : Layer("Start Layer")
	{
		x = 0, y = 0;
		xv = 0, yv = 0;
		/*m_VertexArray.reset(Swallow::VertexArray::Create());
		m_VertexArray->Bind();

		float vertices[3 * 7] = {
			 0.0f, 0.5f,  0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
			-0.5f, -0.5f,  0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
			 0.5f, -0.5f,  0.0f, 0.2f, 0.2f, 0.8f, 1.0f
		};

		std::shared_ptr<Swallow::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Swallow::VertexBuffer::Create(vertices, sizeof(vertices)));


		vertexBuffer->SetLayout({
			{ Swallow::ShaderDataType::Float3, "a_Position" },
			{ Swallow::ShaderDataType::Float4, "a_Color" , true }
			});

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		uint32_t indices[3] = {
			0, 1, 2
		};

		std::shared_ptr<Swallow::IndexBuffer> indexBuffer;
		indexBuffer.reset(Swallow::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main() {
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec4 v_Color;

			void main() {
				color = v_Color;
			}
		)";

		m_Shader.reset(Swallow::Shader::Create(vertexSrc, fragmentSrc));

		
		m_SquareVA.reset(Swallow::VertexArray::Create());

		float squareBuffer[4 * 3] = {
			 0.05f, -0.05f,  0.0f,
			 0.05f,  0.05f,  0.0f,
			-0.05f,  0.05f,  0.0f,
			-0.05f, -0.05f,  0.0f
		};
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
		*/
		std::string sVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			void main() {
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string sFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			void main() {
				color = vec4(0.2, 0.2, 0.8, 1.0);
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
			xv = 0;
			yv = 0;
		}
		return true;
	}

	virtual void OnImGuiRender() override {
	}

	void OnUpdate() {
		std::shared_ptr<Swallow::VertexArray> m_SquareVA;
		m_SquareVA.reset(Swallow::VertexArray::Create());

		yv -= 0.0005;
		xv = xv < -0.5 ? -0.5 : xv;
		xv = xv > 0.5 ? 0.5 : xv;
		yv = yv < -0.5 ? -0.5 : yv;
		yv = yv > 0.5 ? 0.5 : yv;
		if ((y + yv) < -0.95)
		{
			yv = -yv - 0.005;
			yv = yv > 0 ? yv : 0;
		}
		if ((y + yv) > 0.95)
		{
			yv = -yv + 0.005;
			yv = yv < 0 ? yv : 0;
		}
		if ((x + xv) < -0.95)
		{
			xv = -xv - 0.005;
			xv = xv > 0 ? xv : 0;
		}
		if ((x + xv) > 0.95)
		{
			xv = -xv + 0.005;
			xv = xv < 0 ? xv : 0;
		}
		x += xv;
		y += yv;
		float squareBuffer[4 * 3] = {
			 0.05f + x, -0.05f + y,  0.0f,
			 0.05f + x,  0.05f + y,  0.0f,
			-0.05f + x,  0.05f + y,  0.0f,
			-0.05f + x, -0.05f + y,  0.0f
		};
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

		Swallow::Renderer::BeginScene();

		m_SquareShader->Bind();
		Swallow::Renderer::Submit(m_SquareVA);

		if (Swallow::Input::IsKeyPressed(SW_KEY_LEFT))
		{
			xv -= 0.001;
		//m_Shader->Bind();
		//Swallow::Renderer::Submit(m_VertexArray);
		}
		if (Swallow::Input::IsKeyPressed(SW_KEY_RIGHT))
		{
			xv += 0.001;
		}
		if (Swallow::Input::IsKeyPressed(SW_KEY_DOWN))
		{
			yv -= 0.001;
		}
		if (Swallow::Input::IsKeyPressed(SW_KEY_UP))
		{
			yv += 0.001;
		}

		Swallow::Renderer::EndScene();
		auto[x, y] = Swallow::Input::GetMousePosition();
		if (Swallow::Input::IsKeyPressed(SW_KEY_LEFT_CONTROL))
			SW_CORE_TRACE("{0}, {1}", x, y);
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