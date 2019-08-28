/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureInstance.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 15:37:24 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 16:54:00 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Platform/OpenGL/OpenGLShader.hpp"
#include "Platform/OpenGL/OpenGLTexture.hpp"

namespace Swallow {
    class TextureInstance
    {
        public:
            TextureInstance();
            TextureInstance(TextureInstance const &rhs);
            TextureInstance &operator=(TextureInstance const &rhs);
            virtual ~TextureInstance();
            
            inline Ref<Shader> GetTexture() { return m_Texture;}
            inline Ref<Texture2D> GetTextureImage() { return m_TextureImage;}
            virtual void Bind() = 0;
            virtual void Unbind() = 0;
        protected:
            Ref<Shader> m_Texture;
            Ref<Texture2D> m_TextureImage;
    };
}