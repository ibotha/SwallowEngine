#pragma once

#include <glm.hpp>
#include <Swallow/Renderer/Camera.hpp>
#include <Swallow/Renderer/VertexArray.hpp>
#include <Swallow/Renderer/Shader.hpp>

namespace Swallow
{

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primatives
		static void DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 & color, float rotation = 0.0f);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation = 0.0f);
	};

}