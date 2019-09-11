/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureMaterialInstance.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:09:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/30 14:44:02 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "TextureInstance.hpp"

namespace Swallow {

    class TextureMaterialInstance: public TextureInstance
    {
        public:
            TextureMaterialInstance(Ref<Shader> shader);
            TextureMaterialInstance(Ref<Shader> shader, Ref<Texture2D> texture);
            TextureMaterialInstance(TextureMaterialInstance const &rhs);
            TextureMaterialInstance &operator=(TextureMaterialInstance const &rhs);
            ~TextureMaterialInstance();

            void Bind();
            void Unbind();

            void SetLightDirection(glm::vec3 LightDirection);
            void SetViewProjection(glm::mat4 ViewProjection);
            void SetRot(glm::mat4 Rot);
            void SetModel(glm::mat4 Model);
            
            glm::vec3 GetLightDirection();
            glm::mat4 GetViewProjection();
            glm::mat4 GetRot();
            glm::mat4 GetModel();
        private:
            TextureMaterialInstance();
            glm::vec3 m_LightDirection;
            glm::mat4 m_ViewProjection;
            glm::mat4 m_Rot;
            glm::mat4 m_Model;
    };
}
