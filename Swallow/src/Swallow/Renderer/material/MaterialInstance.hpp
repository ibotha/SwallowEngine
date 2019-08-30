/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MaterialInstance.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 14:09:25 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/30 12:23:02 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Platform/OpenGL/OpenGLShader.hpp"
#include "Platform/OpenGL/OpenGLTexture.hpp"

namespace Swallow {
    class MaterialInstance
    {
        public:
            MaterialInstance();
            MaterialInstance(MaterialInstance const &rhs);
            MaterialInstance &operator=(MaterialInstance const &rhs);
            virtual ~MaterialInstance();
            
            inline Ref<Shader> GetShader() { return m_Shader; }
            virtual void Bind() = 0;
            virtual void Unbind() = 0;

        protected:
            Ref<Shader> m_Shader;

    };
}