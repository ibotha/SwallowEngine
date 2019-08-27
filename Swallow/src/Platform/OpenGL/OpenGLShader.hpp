#pragma once
#include "Swallow/Renderer/Shader.hpp"

namespace Swallow {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const char *vertexPath, const char *fragmentPath);
		OpenGLShader(const OpenGLShader &rhs) = default;
		OpenGLShader &operator=(const OpenGLShader &rhs) = default;
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void UploadUniformFloat1(std::string const &name, glm::vec1 const &v);
		virtual void UploadUniformFloat2(std::string const &name, glm::vec2 const &v);
		virtual void UploadUniformFloat3(std::string const &name, glm::vec3 const &v);
		virtual void UploadUniformFloat4(std::string const &name, glm::vec4 const &v);
		virtual void UploadUniformInt1(std::string const &name, glm::ivec1 const &v);
		virtual void UploadUniformInt2(std::string const &name, glm::ivec2 const &v);
		virtual void UploadUniformInt3(std::string const &name, glm::ivec3 const &v);
		virtual void UploadUniformInt4(std::string const &name, glm::ivec4 const &v);
		virtual void UploadUniformMat2(std::string const &name, glm::mat2 const &v);
		virtual void UploadUniformMat3(std::string const &name, glm::mat3 const &v);
		virtual void UploadUniformMat4(std::string const &name, glm::mat4 const &v);

	private:
		uint32_t m_RendererID;
		void initialise(const std::string &vertexSrc, const std::string &fragmentPath);
	};
}