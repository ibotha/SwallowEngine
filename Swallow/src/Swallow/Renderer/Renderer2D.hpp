#pragma once

#include <glm.hpp>
#include <Swallow/Renderer/Texture.hpp>
#include <Swallow/Renderer/SubTexture.h>
#include <Swallow/Renderer/Camera.hpp>

namespace Swallow
{


	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primatives
		static void DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 & color, float rotation = 0.0f, float tillingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation = 0.0f, float tillingFactor = 1.0f);

		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<Texture2D> texture, float rotation = 0.0f, float tillingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture2D> texture, float rotation = 0.0f, float tillingFactor = 1.0f);

		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<Texture2D> texture, float rotation = 0.0f, const glm::vec4& color = { 1.0f,1.0f,1.0f, 1.0f }, float tillingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture2D> texture, float rotation = 0.0f, const glm::vec4& color = { 1.0f,1.0f,1.0f, 1.0f }, float tillingFactor = 1.0f);

		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<SubTexture2D> texture, float rotation = 0.0f, const glm::vec4& color = {1.0f,1.0f,1.0f, 1.0f}, float tillingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, Ref<SubTexture2D> texture, float rotation = 0.0f, const glm::vec4& color = { 1.0f,1.0f,1.0f, 1.0f }, float tillingFactor = 1.0f);

		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		static Statistics GetStatistics();
		static void ResetStatistics();

	private:
		static float BindBatchedTexture(Ref<Texture2D> texture);
		static void UploadVerts(float textureIndex, float tillingFactor, const glm::vec4* verts, const glm::vec4& color, const glm::vec2* texCoods);
		static void FillQuadVerts(glm::vec4* verts, const glm::vec3& pos, const glm::vec2& size, float rotation);
	};

}