#pragma once

#include <glm.hpp>
#include <Swallow/Renderer/Camera.hpp>
#include <Swallow/Renderer/VertexArray.hpp>
#include <Swallow/Renderer/Shader.hpp>
#include <Swallow/Renderer/Texture.hpp>

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
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, Ref<Texture2D> texture, float rotation = 0.0f, float tillingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, Ref<Texture2D> texture, float rotation = 0.0f, float tillingFactor = 1.0f);

		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		static Statistics GetStatistics();
		static void ResetStatistics();
	};

}