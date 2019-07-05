#include "swpch.h"
#include "Renderer.h"

namespace Swallow {

	void Renderer::BeginScene(Camera const &c)
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}