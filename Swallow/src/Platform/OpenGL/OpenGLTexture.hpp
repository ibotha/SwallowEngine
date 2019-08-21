#pragma once
#include "Swallow/Renderer/Texture.hpp"

namespace Swallow {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(const OpenGLTexture2D &rhs) = default;
		OpenGLTexture2D &operator=(const OpenGLTexture2D &rhs) = default;
		virtual ~OpenGLTexture2D();

		// Inherited via Texture2D
		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual void Bind(uint32_t slot = 0) const override;
	private:

		uint32_t ChannelType(int channel);
		uint32_t m_Width, m_Height;
		std::string m_Path;

		uint32_t m_RendererID;
	};

}