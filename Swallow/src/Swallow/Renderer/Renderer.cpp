#include "swpch.h"
#include "Renderer.h"

namespace Swallow {

	Renderer::SceneData *Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera &c)
	{
		s_SceneData->ViewProjectionMatrix = c.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniform("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}