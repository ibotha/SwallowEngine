#pragma once

namespace Swallow {
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		inline uint32_t getRendererID() { return m_RendererID; }
	private:
		uint32_t m_RendererID;
	};
}