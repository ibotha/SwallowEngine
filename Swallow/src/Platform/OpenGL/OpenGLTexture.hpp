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

		unsigned int ChannelType(int channel);
		unsigned int InternalChannelType(int channel);
		uint32_t m_Width, m_Height;
		std::string m_Path;

		uint32_t m_RendererID;
	};

	class OpenGLCharacter : public Character
	{
	public:
		OpenGLCharacter(const FT_GlyphSlot glyph);
		OpenGLCharacter(const OpenGLCharacter &rhs) = default;
		OpenGLCharacter &operator=(const OpenGLCharacter &rhs) = default;
		virtual ~OpenGLCharacter() = default;

		// Inherited via Texture2D
		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual uint32_t GetTop() const override;
		virtual uint32_t GetLeft() const override;
		virtual void Bind(uint32_t slot = 0) const override;
	private:

		unsigned int ChannelType(int channel);
		unsigned int InternalChannelType(int channel);
		uint32_t m_Width, m_Height;
		uint32_t m_Left, m_Top;

		uint32_t m_RendererID;
	};

}