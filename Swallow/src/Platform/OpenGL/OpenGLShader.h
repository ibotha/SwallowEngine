#pragma once
#include "Swallow/Renderer/Shader.h"

namespace Swallow {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void UploadUniform(std::string const &name, glm::vec1 const &v) override;
		virtual void UploadUniform(std::string const &name, glm::vec2 const &v) override;
		virtual void UploadUniform(std::string const &name, glm::vec3 const &v) override;
		virtual void UploadUniform(std::string const &name, glm::vec4 const &v) override;
		virtual void UploadUniform(std::string const &name, glm::ivec1 const &v) override;
		virtual void UploadUniform(std::string const &name, glm::ivec2 const &v) override;
		virtual void UploadUniform(std::string const &name, glm::ivec3 const &v) override;
		virtual void UploadUniform(std::string const &name, glm::ivec4 const &v) override;
		virtual void UploadUniform(std::string const &name, glm::mat2 const &v) override;
		virtual void UploadUniform(std::string const &name, glm::mat3 const &v) override;
		virtual void UploadUniform(std::string const &name, glm::mat4 const &v) override;

	private:
		uint32_t m_RendererID;
	};
}