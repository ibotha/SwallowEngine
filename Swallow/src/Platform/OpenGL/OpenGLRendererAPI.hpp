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


		// Inherited via RendererAPI
		virtual void SetClearColor(const glm::vec4 & color) override;

		virtual void SetDepthTest(bool val) override;

		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	};

}