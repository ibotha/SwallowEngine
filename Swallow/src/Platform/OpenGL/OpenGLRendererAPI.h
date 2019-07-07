#pragma once

#include "Swallow/Renderer/RendererAPI.h"

namespace Swallow {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI();
		~OpenGLRendererAPI();

	private:


		// Inherited via RendererAPI
		virtual void SetClearColor(const glm::vec4 & color) override;

		virtual void SetDepthTest(bool val) override;

		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	};

}