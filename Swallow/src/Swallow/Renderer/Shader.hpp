#pragma once
#include "swpch.hpp"

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

		static Ref<Shader> Create(const std::string & vertexSrc, const std::string & fragmentSrc);
	};
}