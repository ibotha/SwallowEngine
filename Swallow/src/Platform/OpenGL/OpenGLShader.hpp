#pragma once
#include "Swallow/Renderer/Shader.hpp"

//TODO: FIX THIS
typedef unsigned int GLenum;

namespace Swallow {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string & vertexPath, const std::string & fragmentPath);
		OpenGLShader(const OpenGLShader &rhs) = default;
		OpenGLShader &operator=(const OpenGLShader &rhs) = default;
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const std::string &GetName() const override;

		virtual void UploadUniformFloat(std::string const &name, float v);
		virtual void UploadUniformFloat2(std::string const &name, glm::vec2 const &v);
		virtual void UploadUniformFloat3(std::string const &name, glm::vec3 const &v);
		virtual void UploadUniformFloat4(std::string const &name, glm::vec4 const &v);
		virtual void UploadUniformInt(std::string const &name, int v);
		virtual void UploadUniformInt2(std::string const &name, glm::ivec2 const &v);
		virtual void UploadUniformInt3(std::string const &name, glm::ivec3 const &v);
		virtual void UploadUniformInt4(std::string const &name, glm::ivec4 const &v);
		virtual void UploadUniformIntArray(std::string const& name, int* v, uint32_t count);
		virtual void UploadUniformMat2(std::string const &name, glm::mat2 const &v);
		virtual void UploadUniformMat3(std::string const &name, glm::mat3 const &v);
		virtual void UploadUniformMat4(std::string const &name, glm::mat4 const &v);

		virtual void SetFloat(std::string const &name, float v) override;
		virtual void SetFloat2(std::string const &name, glm::vec2 const &v) override;
		virtual void SetFloat3(std::string const &name, glm::vec3 const &v) override;
		virtual void SetFloat4(std::string const &name, glm::vec4 const &v) override;
		virtual void SetInt(std::string const& name, int v) override;
		virtual void SetInt2(std::string const &name, glm::ivec2 const &v) override;
		virtual void SetInt3(std::string const &name, glm::ivec3 const &v) override;
		virtual void SetInt4(std::string const &name, glm::ivec4 const &v) override;
		virtual void SetIntArray(std::string const &name, int* v, uint32_t count) override;
		virtual void SetMat2(std::string const &name, glm::mat2 const &v) override;
		virtual void SetMat3(std::string const &name, glm::mat3 const &v) override;
		virtual void SetMat4(std::string const &name, glm::mat4 const &v) override;

		int32_t GetUniform(const std::string &name);

	private:
		std::string ReadFile(const std::string& filepath);
		void Compile(const std::unordered_map<GLenum, std::string> &sources);
	private:
		std::string m_Name;
		RendererID m_RendererID;
		std::unordered_map<std::string, int32_t> m_Uniforms;
	};
}