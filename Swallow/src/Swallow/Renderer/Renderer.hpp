#pragma once
#include "Camera.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
#include "../AssetManager/GameObject.hpp"

#include "RenderCommand.hpp"
// TODO: Remove
#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Swallow {

	class Renderer
	{
	public:

		Renderer();
		Renderer(const Renderer&);
		~Renderer();
		Renderer &operator=(const Renderer&);

		static void Init();

		static void BeginScene(Camera& c);
		static void EndScene();

		static void Submit(const Ref<GameObject>& object);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* s_SceneData;
	};
}