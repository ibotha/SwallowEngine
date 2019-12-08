#include "swpch.hpp"
#include "Renderer.hpp"

namespace Swallow {

	Renderer::SceneData *Renderer::s_SceneData = new Renderer::SceneData;

	Renderer::Renderer(){}
	Renderer::Renderer(const Renderer& cpy)
	{
		if (this != &cpy)
			*this = cpy;
	}
	Renderer::~Renderer(){}
	
	Renderer &Renderer::operator=(const Renderer& rhs)
	{
		if (this != &rhs)
			*this = rhs;
		return *this;
	}

	void Renderer::Init()
	{
		SW_PROFILE_FUNCTION();
		RenderCommand::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		SW_PROFILE_FUNCTION();
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const Camera &c)
	{
		SW_PROFILE_FUNCTION();
		s_SceneData->ViewProjectionMatrix = c.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
		SW_PROFILE_FUNCTION();
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		SW_PROFILE_FUNCTION();
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Model", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}