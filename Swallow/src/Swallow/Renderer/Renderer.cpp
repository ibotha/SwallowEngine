#include "swpch.hpp"
#include "Renderer.hpp"
#include "gtx/transform.hpp"

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
		RenderCommand::Init();
	}

	void Renderer::BeginScene(Camera &c)
	{
		s_SceneData->ViewProjectionMatrix = c.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(Ref<GameObject>& object)
	{
		object->GetMaterial()->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(object->GetMaterial()->GetShader())->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(object->GetMaterial()->GetShader())->UploadUniformMat4("u_Rot", glm::identity<glm::mat4>());
		std::dynamic_pointer_cast<OpenGLShader>(object->GetMaterial()->GetShader())->UploadUniformMat4("u_Model", object->GetTransform()->GetModelMatrix());
		object->GetVertexArray()->Bind();
		RenderCommand::DrawIndexed(object->GetVertexArray());
	}
}