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
		virtual const std::string &GetName() const = 0;

		static Ref<Shader> Create(const std::string& name, const std::string & vertexSrc, const std::string & fragmentSrc);
		static Ref<Shader> Create(const std::string& name, const std::string &filepath);
		static Ref<Shader> Create(const std::string &filepath);
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, std::string& filepath);
		Ref<Shader> Load(const std::string& name, std::string& vertexSource, std::string& fragmentSource);
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