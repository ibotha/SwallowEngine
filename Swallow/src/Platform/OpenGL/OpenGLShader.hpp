#pragma once
#include "Swallow/Renderer/Shader.hpp"

//TODO: FIX THIS
typedef unsigned int GLenum;

namespace Swallow {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string & vertexSrc, const std::string & fragmentSrc);
		OpenGLShader(const std::string& name, const std::string &filepath);
		OpenGLShader(const std::string &filepath);
		OpenGLShader(const OpenGLShader &rhs) = default;
		OpenGLShader &operator=(const OpenGLShader &rhs) = default;
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const std::string &GetName() const override;

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
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string> &sources);
	private:
		std::string m_Name;
		uint32_t m_RendererID;
	};
}