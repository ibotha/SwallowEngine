#include "swpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Swallow {

	OpenGLRendererAPI::OpenGLRendererAPI()
	{
	}

	OpenGLRendererAPI::~OpenGLRendererAPI()
	{
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4 & color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::SetDepthTest(bool val)
	{
		if (val)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}