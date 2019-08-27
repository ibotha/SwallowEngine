/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MaterialInstance.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 14:09:25 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/27 13:38:15 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Platform/OpenGL/OpenGLShader.hpp"
#include "Platform/OpenGL/OpenGLTexture.hpp"

// class FlatColourMaterialInstance
// {
//     virtual void Bind();

//     private:
//         glm::vec3 m_Colour;
//         Swallow::Ref<Shader> m_Shader;

// };

// class FlatColourMaterial
// {
//     static Swallow::Ref<FlatColourMaterialInstance> Create();
// };

namespace Swallow {
    class MaterialInstance
    {
        public:
            MaterialInstance();
            MaterialInstance(MaterialInstance const &rhs);
            MaterialInstance &operator=(MaterialInstance const &rhs);
            virtual ~MaterialInstance();

        protected:
            virtual void Bind() = 0;
            virtual void Unbind() = 0;

    };
}