#pragma once

#include "Swallow/Renderer/RendererAPI.hpp"

namespace Swallow {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI();
		OpenGLRendererAPI(const OpenGLRendererAPI &rhs) = default;
		OpenGLRendererAPI &operator=(const OpenGLRendererAPI &rhs) = default;
		virtual ~OpenGLRendererAPI();

	private:

		virtual void Init();

		// Inherited via RendererAPI
		virtual void SetClearColor(const glm::vec4 & color) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void Clear() override;
		virtual void ClearColour() override;
		virtual void ClearDepth() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	};

}