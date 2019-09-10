#include "swpch.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Swallow {

	Shader::Shader(){}
	Shader::Shader(const Shader& cpy)
	{
		if (this != &cpy)
			*this = cpy;
	}

	Shader &Shader::operator=(const Shader& rhs)
	{
		if (this != &rhs)
			*this = rhs;
		return *this;
	}

	Ref<Shader> Shader::Create(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		default:
			break;
	}
	return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string &filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		default:
			break;
	}
	return nullptr;
	}
}