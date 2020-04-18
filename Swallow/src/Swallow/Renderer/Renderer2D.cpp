#include <swpch.hpp>
#include <gtc/matrix_transform.hpp>
#include <Swallow/Renderer/Renderer2D.hpp>
#include <Swallow/Renderer/RenderCommand.hpp>
#include <list>

namespace Swallow {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TextureIndexSlot;
		float TilingFactor;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: Get from GL

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> Shader;
		Ref<Texture2D> BaseTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 0;

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData s_Data;

	static void StartNewBatch() {
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 0;
		for (auto& i : s_Data.TextureSlots)
			i = 0;
	}

	void Renderer2D::Init()
	{
		SW_PROFILE_FUNCTION();

		s_Data.BaseTexture = Texture2D::Create(1, 1);
		unsigned char data[] = {
			255, 255, 255, 255
		};
		s_Data.BaseTexture->SetData(data, sizeof(data));

		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Colour" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" }
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndeces = new uint32_t[s_Data.MaxIndices];
		for (uint32_t offset = 0, i = 0; i < s_Data.MaxIndices; i += 6, offset += 4)
		{
			quadIndeces[i + 0] = offset + 0;
			quadIndeces[i + 1] = offset + 1;
			quadIndeces[i + 2] = offset + 2;

			quadIndeces[i + 3] = offset + 2;
			quadIndeces[i + 4] = offset + 3;
			quadIndeces[i + 5] = offset + 0;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndeces, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndeces;
		s_Data.Shader = Shader::Create("2drenderer", "assets/Shaders/2Drenderervertex.glsl" , "assets/Shaders/2Drendererfragment.glsl");

		s_Data.Shader->Bind();

		int samplers[s_Data.MaxTextureSlots];
		for (int i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;
		s_Data.Shader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data.Shader->Bind();
		s_Data.Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		StartNewBatch();
	}

	void Renderer2D::EndScene()
	{
		Flush();
	}

	void Renderer2D::Flush()
	{
		uint32_t dataSize = (s_Data.QuadVertexBufferPtr - s_Data.QuadVertexBufferBase) * sizeof(QuadVertex);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		for (int i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float rotation, float tillingFactor)
	{
		DrawQuad(glm::vec3(pos.x, pos.y, 0.0f), size, color, rotation, tillingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation, float tillingFactor)
	{
		DrawQuad(pos, size, color, s_Data.BaseTexture, rotation, tillingFactor);
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
		float textureIndex = -1;
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			if (*texture == *s_Data.TextureSlots[i])
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == -1.0f)
		{
			if (s_Data.TextureSlotIndex == s_Data.MaxTextureSlots)
			{
				Flush();
				StartNewBatch();
				s_Data.TextureSlotIndex = 0;
				for (auto& i : s_Data.TextureSlots)
					i = 0;
			}
			textureIndex = (float)s_Data.TextureSlotIndex++;
			s_Data.TextureSlots[textureIndex] = texture;
		}

		glm::vec2 nsize = size / 2.0f;
		glm::vec4 verts[4] = {
			{-nsize.x, -nsize.y, 0.0f, 1.0f},
			{nsize.x, -nsize.y, 0.0f, 1.0f},
			{nsize.x, nsize.y, 0.0f, 1.0f},
			{-nsize.x, nsize.y, 0.0f, 1.0f}
		};
		if (rotation != 0.0f)
		{
			glm::mat4 t = glm::rotate(glm::identity<glm::mat4>(), rotation, { 0.0f, 0.0f, 1.0f });
			for (int i = 0; i < 4; i++)
				verts[i] = t * verts[i];
		}

		s_Data.QuadVertexBufferPtr->Position = { pos.x + verts[0].x, pos.y + verts[0].y, pos.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TextureIndexSlot = textureIndex;
		s_Data.QuadVertexBufferPtr->TilingFactor = tillingFactor;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->TextureIndexSlot = textureIndex;
		s_Data.QuadVertexBufferPtr->TilingFactor = tillingFactor;
		s_Data.QuadVertexBufferPtr->Position = { pos.x + verts[1].x, pos.y + verts[1].y, pos.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->TextureIndexSlot = textureIndex;
		s_Data.QuadVertexBufferPtr->TilingFactor = tillingFactor;
		s_Data.QuadVertexBufferPtr->Position = { pos.x + verts[2].x, pos.y + verts[2].y, pos.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->TextureIndexSlot = textureIndex;
		s_Data.QuadVertexBufferPtr->TilingFactor = tillingFactor;
		s_Data.QuadVertexBufferPtr->Position = { pos.x + verts[3].x, pos.y + verts[3].y, pos.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;
		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;

		if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
		{
			Flush();
			StartNewBatch();
		}
	}

	Renderer2D::Statistics Renderer2D::GetStatistics()
	{
		return s_Data.Stats;
	}

	void Renderer2D::ResetStatistics()
	{
		s_Data.Stats.DrawCalls = 0;
		s_Data.Stats.QuadCount = 0;
	}

}