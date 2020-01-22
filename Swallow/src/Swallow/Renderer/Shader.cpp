#include "swpch.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Swallow {

	Shader::Shader() {}
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

	Ref<Shader> Shader::Create(const std::string & name, const std::string & vertexPath, const std::string & fragmentPath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(name, vertexPath, fragmentPath);
		default:
			break;
		}
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		const std::string& name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const std::string & name, const Ref<Shader>& shader)
	{
		if (!Exists(name))
			m_Shaders[name] = shader;
		else
			SW_CORE_WARN("Shader not added! Duplicate shader: {}", name);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string & name, const std::string & vertexSource, const std::string & fragmentSource)
	{
		Ref<Shader> shader = Shader::Create(name, vertexSource, fragmentSource);

		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string & name)
	{
		SW_CORE_ASSERT(Exists(name), "Missing Shader! {}", name);
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string & name) const
	{
		return (m_Shaders.find(name) != m_Shaders.end());
	}
}