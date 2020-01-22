#include "swpch.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLTexture.hpp"

namespace Swallow {

	Texture2D::Texture2D(){}
	Texture2D::Texture2D(const Texture2D& cpy)
	{
		if (this != &cpy)
			*this = cpy;
	}
	Texture2D &Texture2D::operator=(const Texture2D& rhs)
	{
		if (this != &rhs)
			*this = rhs;
		return *this;
	}

	Ref<Texture2D> Texture2D::Create(const std::string & path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(path);
		default:
			break;
		}
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height);
		default:
			break;
		}
		return nullptr;
	}

}