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

		virtual void Init() override;

		// Inherited via RendererAPI
		virtual void SetClearColor(const glm::vec4 & color) override;

		virtual void Clear() override;
		virtual void ClearColour() override;
		virtual void ClearDepth() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	};

}