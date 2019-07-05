#pragma once
namespace Swallow {

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniform(std::string const &name, glm::vec1 const &v) = 0;
		virtual void UploadUniform(std::string const &name, glm::vec2 const &v) = 0;
		virtual void UploadUniform(std::string const &name, glm::vec3 const &v) = 0;
		virtual void UploadUniform(std::string const &name, glm::vec4 const &v) = 0;
		virtual void UploadUniform(std::string const &name, glm::ivec1 const &v) = 0;
		virtual void UploadUniform(std::string const &name, glm::ivec2 const &v) = 0;
		virtual void UploadUniform(std::string const &name, glm::ivec3 const &v) = 0;
		virtual void UploadUniform(std::string const &name, glm::ivec4 const &v) = 0;
		virtual void UploadUniform(std::string const &name, glm::mat2 const &v) = 0;
		virtual void UploadUniform(std::string const &name, glm::mat3 const &v) = 0;
		virtual void UploadUniform(std::string const &name, glm::mat4 const &v) = 0;

		static Shader* Create(const std::string & vertexSrc, const std::string & fragmentSrc);
	};
}