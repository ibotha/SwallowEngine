#include "swpch.hpp"
#include "OpenGLTexture.hpp"
#include <glad/glad.h>
#include <stb_image.h>

namespace Swallow {
	OpenGLTexture2D::OpenGLTexture2D(const std::string & path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc * data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		SW_CORE_ASSERT(data, "Failed to load image! {}", path);
		m_Width = width;
		m_Height = height;

#ifdef MODERN_GL
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, InternalChannelType(channels), m_Width, m_Height);
#else
		glActiveTexture(GL_TEXTURE31);
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
#endif
		float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glTexParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

#ifdef MODERN_GL
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, ChannelType(channels), GL_UNSIGNED_BYTE, data);
#else
		glTexImage2D(GL_TEXTURE_2D, 0, InternalChannelType(channels), m_Width, m_Height, 0, ChannelType(channels), GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
#endif

		stbi_image_free(data);
	}
	
	GLenum OpenGLTexture2D::ChannelType(int channel)
	{
		SW_CORE_INFO("Channels in image: {}", channel);
		switch (channel)
		{
		case 1:
			return (GL_RED);
			break;
		case 2:
			return (GL_RG);
			break;
		case 3:
			return (GL_RGB);
			break;
		case 4:
			return (GL_RGBA);
			break;
		
		default:
			return (GL_RGB);
			break;
		}
		return (GL_RGB);
	}

	GLenum OpenGLTexture2D::InternalChannelType(int channel)
	{
		SW_CORE_INFO("Channels in image: {}", channel);
		switch (channel)
		{
		case 1:
			return (GL_RGB8);
			break;
		case 2:
			return (GL_RGB8);
			break;
		case 3:
			return (GL_RGB8);
			break;
		case 4:
			return (GL_RGBA8);
			break;

		default:
			return (GL_RGB8);
			break;
		}
		return (GL_RGB8);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	uint32_t OpenGLTexture2D::GetWidth() const
	{
		return m_Width;
	}

	uint32_t OpenGLTexture2D::GetHeight() const
	{
		return m_Height;
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

}