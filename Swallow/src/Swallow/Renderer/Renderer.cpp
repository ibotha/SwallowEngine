#include "swpch.hpp"
#include "Renderer.hpp"

namespace Swallow {

	Renderer::SceneData *Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera &c)
	{
		s_SceneData->ViewProjectionMatrix = c.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<OpenGLShader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Model", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}