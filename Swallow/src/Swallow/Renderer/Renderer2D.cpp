#include <swpch.hpp>
#include <gtc/matrix_transform.hpp>
#include <Swallow/Renderer/Renderer2D.hpp>
#include <Swallow/Renderer/RenderCommand.hpp>
#include <list>

namespace Swallow {
	struct Renderer2DCommand
	{
		Ref<Texture2D> texture;
		glm::mat4 matrix;
		glm::vec4 tillingFactor;
		glm::vec4 colour;
	};

	struct Renderer2DData
	{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> shader;
		Ref<Texture2D> baseTexture;
		std::list<Renderer2DCommand> renderQueue;
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

		s_data->quadVertexArray = VertexArray::Create();
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
		s_data->quadVertexArray->AddVertexBuffer(VB);
		uint32_t Indeces[] = {
			0, 1, 2,
			2, 3, 0
		};
		Ref<IndexBuffer> IB = IndexBuffer::Create(Indeces, 6);
		s_data->quadVertexArray->SetIndexBuffer(IB);
		s_data->shader = Shader::Create("2drenderer", "assets/Shaders/2Drenderervertex.glsl" , "assets/Shaders/2Drendererfragment.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_data->renderQueue.clear();
		s_data->shader->Bind();
		s_data->shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_data->shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float rotation, float tillingFactor)
	{
		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, color, rotation, tillingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation, float tillingFactor)
	{
		DrawQuad(pos, size, color, s_data->baseTexture, rotation, tillingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<Texture2D> texture, float rotation, float tillingFactor)
	{
		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, texture, rotation, tillingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture2D> texture, float rotation, float tillingFactor)
	{
		DrawQuad(pos, size, { 1, 1, 1, 1 }, texture, rotation, tillingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, Ref<Texture2D> texture, float rotation, float tillingFactor)
	{
		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, color, texture, rotation, tillingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, Ref<Texture2D> texture, float rotation, float tillingFactor)
	{
		s_data->shader->Bind();
		glm::mat4 transform = glm::identity<glm::mat4>();
		transform = glm::translate(transform, pos);
		if (rotation)
		{
			transform = glm::rotate(transform, rotation, { 0, 0, 1 });
		}
		transform = glm::scale(transform, { size.x, size.y, 1 });

		s_data->shader->SetMat4("u_Model", transform);
		s_data->shader->SetFloat4("u_Colour", color);
		s_data->shader->SetFloat("u_TillingFactor", tillingFactor);
		texture->Bind(0);
		RenderCommand::DrawIndexed(s_data->quadVertexArray);
	}

}