#include "swpch.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Swallow {

	VertexArray::VertexArray(){}
	VertexArray::VertexArray(const VertexArray& cpy)
	{
		if (this != &cpy)
			*this = cpy;
	}
	VertexArray &VertexArray::operator=(const VertexArray& rhs)
	{
		if (this != &rhs)
			*this = rhs;
		return *this;
	}

	Ref<VertexArray> VertexArray::Create()
	{
		SW_PROFILE_FUNCTION();
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		default:
			break;
		}
		return nullptr;
	}
}