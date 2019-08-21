#include "swpch.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLTexture.hpp"

namespace Swallow {



	Ref<Texture2D> Texture2D::Create(const std::string & path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		default:
			break;
		}
		return nullptr;
	}

}