/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MaterialInstance.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 14:09:25 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 13:34:14 by ibotha           ###   ########.fr       */
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
            inline Ref<Shader> GetShader() { return m_Shader; }

        protected:
            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            Ref<Shader> m_Shader;

    };
}