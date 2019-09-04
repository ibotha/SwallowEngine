/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextTexture.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 11:57:37 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/04 16:20:36 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swpch.hpp"
#include "TextTexture.hpp"

namespace Swallow
{
    TextTexture::TextTexture()
    {
        int error = FT_Init_FreeType(&m_FT);
        if (error)
        {
            SW_CORE_ASSERT(!error, "FreeType could not be initialised");
        }
        error = FT_New_Face(m_FT, "assets/fonts/Arial.ttf", 0, &m_Arial);
        if (error)
        {
            SW_CORE_ASSERT(!error, "Arial font face could not be initialised");
        }
        FT_Set_Pixel_Sizes(m_Arial, 0, 48);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        for (GLubyte c = 0; c < 128; c++)
        {
            if (FT_Load_Char(m_Arial, c, FT_LOAD_RENDER))
            {
                SW_CORE_WARN("FreeType could not load character: {}", c);
                continue ;
            }

            #ifdef MODERN_GL
                    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
                    glTextureStorage2D(m_RendererID, 1, InternalChannelType(channels), m_Width, m_Height);
            #else
                    glActiveTexture(GL_TEXTURE31);
                    glGenTextures(1, &m_RendererID);
                    glBindTexture(GL_TEXTURE_2D, m_RendererID);
            #endif
                    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            #ifdef MODERN_GL
                    glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, ChannelType(channels), GL_UNSIGNED_BYTE, data);
            #else
                    glTexImage2D(GL_TEXTURE_2D, 
                                0, 
                                GL_RED, 
                                m_Arial->glyph->bitmap.width, 
                                m_Arial->glyph->bitmap.rows,                                 
                                0, 
                                GL_RED, 
                                GL_UNSIGNED_BYTE, 
                                m_Arial->glyph->bitmap.buffer);

                    s_Character character = {
                        m_RendererID,
                        glm::ivec2(m_Arial->glyph->bitmap.width, m_Arial->glyph->bitmap.rows),
                        glm::ivec2(m_Arial->glyph->bitmap_left, m_Arial->glyph->bitmap_top),
                        m_Arial->glyph->advance.x
                    };
                    m_Characters.insert(std::pair<GLchar, s_Character>(c, character));
                    glGenerateMipmap(GL_TEXTURE_2D);
            #endif
        }
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        FT_Done_Face(m_Arial);
        FT_Done_FreeType(m_FT);
    }

    TextTexture::TextTexture(TextTexture const &rhs)
    {
        *this = rhs;
    }

    TextTexture &TextTexture::operator=(TextTexture const &rhs)
    {
        if (this != &rhs)
        {
            *this = rhs;
        }
        return *this;
    }

    TextTexture::~TextTexture()
    {}

    uint32_t TextTexture::GetWidth() const
    {
        return m_Width;
    }

    uint32_t TextTexture::GetHeight() const
    {
        return m_Height;
    }

    void TextTexture::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

    void TextTexture::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        std::string::const_iterator ci;
        for (ci = text.begin(); ci != text.end)_; ci++)
        {
            s_Character character = m_Characters[*ci];
            GLfloat xpos = x + character.Bearing.x * scale;
            GLfloat ypos = y (character.Size.y - character.Bearing.y) * scale;
            GLfloat w = character.Size.x * scale;
            GLfloat h = character.Size.y * scale;
            
            GLfloat vertices[6][4] = {
                { xpos, ypos + h,       0.0, 0.0 },
                { xpos, ypos,           0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                
                { xpos, ypos + h,       0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
            }
            glBindTexture(GL_TEXTURE_2D, m_RendererID);
            x += (character.Advance >> 6) * scale;
        }
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }
}