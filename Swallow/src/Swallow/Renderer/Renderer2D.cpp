#include <swpch.hpp>
#include <gtc/matrix_transform.hpp>
#include <Swallow/Renderer/Renderer2D.hpp>
#include <Swallow/Renderer/RenderCommand.hpp>

namespace Swallow {

	struct Renderer2DData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> Shader;
		Ref<Texture2D> baseTexture;
	};
	static Renderer2DData *s_data;

	void Renderer2D::Init()
	{
		SW_PROFILE_FUNCTION();
		s_data = new Renderer2DData();

		s_data->baseTexture = Texture2D::Create(1, 1);
		unsigned char data[] = {
			255, 255, 255, 255
		};
		s_data->baseTexture->SetData(data, sizeof(data));

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
		s_data->Shader = Shader::Create("assets/Shaders/2DRenderer.glsl");
	}

	void Renderer2D::Shutdown()
	{
		SW_PROFILE_FUNCTION();
		delete s_data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		SW_PROFILE_FUNCTION();
		s_data->Shader->Bind();
		s_data->Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_data->Shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::EndScene()
	{
		SW_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		DrawQuad(pos, size, color, s_data->baseTexture, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<Texture2D> texture, float rotation)
	{
		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, texture, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture2D> texture, float rotation)
	{
		DrawQuad(pos, size, { 1, 1, 1, 1 }, texture, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, Ref<Texture2D> texture, float rotation)
	{

		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, color, texture, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, Ref<Texture2D> texture, float rotation)
	{
		SW_PROFILE_FUNCTION();
		s_data->Shader->Bind();
		glm::mat4 transform = glm::identity<glm::mat4>();
		transform = glm::translate(transform, pos);
		transform = glm::rotate(transform, rotation, { 0, 0, 1 });
		transform = glm::scale(transform, { size.x, size.y, 1 });

		s_data->Shader->SetMat4("u_Model", transform);
		s_data->Shader->SetFloat4("u_Colour", color);
		texture->Bind(0);
		RenderCommand::DrawIndexed(s_data->QuadVertexArray);
	}

}