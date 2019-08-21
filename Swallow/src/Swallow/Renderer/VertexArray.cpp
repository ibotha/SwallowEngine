#include "swpch.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Swallow {
	Ref<VertexArray> VertexArray::Create()
	{
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