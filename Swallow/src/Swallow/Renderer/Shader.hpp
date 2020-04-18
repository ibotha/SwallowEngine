#pragma once

namespace Swallow {

	class Shader
	{
	public:
		virtual ~Shader() {}
		Shader();
		Shader(const Shader&);
		Shader &operator=(const Shader&);
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetFloat(std::string const& name, float v) = 0;
		virtual void SetFloat2(std::string const& name, glm::vec2 const& v) = 0;
		virtual void SetFloat3(std::string const& name, glm::vec3 const& v) = 0;
		virtual void SetFloat4(std::string const& name, glm::vec4 const& v) = 0;
		virtual void SetInt(std::string const& name, int v) = 0;
		virtual void SetInt2(std::string const& name, glm::ivec2 const& v) = 0;
		virtual void SetInt3(std::string const& name, glm::ivec3 const& v) = 0;
		virtual void SetInt4(std::string const& name, glm::ivec4 const& v) = 0;
		virtual void SetIntArray(std::string const& name, int* v, uint32_t count) = 0;
		virtual void SetMat2(std::string const& name, glm::mat2 const& v) = 0;
		virtual void SetMat3(std::string const& name, glm::mat3 const& v) = 0;
		virtual void SetMat4(std::string const& name, glm::mat4 const& v) = 0;

		virtual const std::string &GetName() const = 0;

		static Ref<Shader> Create(const std::string& name, const std::string & vertexPath, const std::string & fragmentPath);
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string &name) const;
		ShaderLibrary() = default;
		ShaderLibrary(const ShaderLibrary&) = default;
		ShaderLibrary &operator=(const ShaderLibrary&) = default;
		~ShaderLibrary() = default;
	private:

		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}