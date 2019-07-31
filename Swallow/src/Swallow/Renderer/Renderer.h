#pragma once
#include "Camera.h"
#include "Buffer.h"
#include "Shader.h"

#include "RenderCommand.h"

namespace Swallow {

	class Renderer
	{
	public:
		static void BeginScene(Camera& c);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* s_SceneData;
	};
}