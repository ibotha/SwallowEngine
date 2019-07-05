#pragma once
#include "Camera.h"
#include "Buffer.h"

#include "RenderCommand.h"

namespace Swallow {

	class Renderer
	{
	public:
		static void BeginScene(Camera const &c);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		Camera m_Camera;
	};
}