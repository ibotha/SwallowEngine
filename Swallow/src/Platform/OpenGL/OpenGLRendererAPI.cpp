#include "swpch.hpp"
#include "OpenGLRendererAPI.hpp"

#include <glad/glad.h>

namespace Swallow {

	OpenGLRendererAPI::OpenGLRendererAPI()
	{
	}

	OpenGLRendererAPI::~OpenGLRendererAPI()
	{
	}

	void OpenGLRendererAPI::Init()
	{
		SW_PROFILE_FUNCTION();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4 & color)
	{
		SW_PROFILE_FUNCTION();
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		SW_PROFILE_FUNCTION();
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::Clear()
	{
		SW_PROFILE_FUNCTION();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void OpenGLRendererAPI::ClearColour()
	{
		SW_PROFILE_FUNCTION();
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void OpenGLRendererAPI::ClearDepth()
	{
		SW_PROFILE_FUNCTION();
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		SW_PROFILE_FUNCTION();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}