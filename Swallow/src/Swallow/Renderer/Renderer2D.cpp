#include <swpch.hpp>
#include <gtc/matrix_transform.hpp>
#include <Swallow/Renderer/Renderer2D.hpp>
#include <Swallow/Renderer/RenderCommand.hpp>

namespace Swallow {

	struct Renderer2DData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> Shader;
	};
	static Renderer2DData *s_data;

	void Renderer2D::Init()
	{
		s_data = new Renderer2DData();

		s_data->QuadVertexArray = VertexArray::Create();
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Ref<VertexBuffer> VB = VertexBuffer::Create(vertices, sizeof(vertices));
		VB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		s_data->QuadVertexArray->AddVertexBuffer(VB);
		uint32_t Indeces[] = {
			0, 1, 2,
			2, 3, 0
		};
		Ref<IndexBuffer> IB = IndexBuffer::Create(Indeces, 6);
		s_data->QuadVertexArray->SetIndexBuffer(IB);
		s_data->Shader = Shader::Create("assets/Shaders/Flatcolour.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_data->Shader->Bind();
		s_data->Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		s_data->Shader->Bind();
		glm::mat4 transform = glm::identity<glm::mat4>();
		transform = glm::translate(transform, pos);
		transform = glm::rotate(transform, rotation, { 0, 0, 1 });
		transform = glm::scale(transform, { size.x, size.y, 1 });

		s_data->Shader->SetMat4("u_Model", transform);
		s_data->Shader->SetFloat4("u_Colour", color);;
		RenderCommand::DrawIndexed(s_data->QuadVertexArray);
	}

}