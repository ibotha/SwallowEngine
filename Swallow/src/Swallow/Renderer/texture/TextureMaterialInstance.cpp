/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureMaterialInstance.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:12:58 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/30 14:23:16 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swpch.hpp"
#include "TextureMaterialInstance.hpp"

namespace Swallow {

    TextureMaterialInstance::TextureMaterialInstance()
    {

    }

    TextureMaterialInstance::TextureMaterialInstance(Ref<Shader> shader)
    {
        m_Texture = shader;
    }

    TextureMaterialInstance::TextureMaterialInstance(Ref<Shader> shader, Ref<Texture2D> texture)
    {
        m_Texture = shader;
        m_TextureImage = texture;
    }

    TextureMaterialInstance::TextureMaterialInstance(TextureMaterialInstance const &rhs)
    {
        *this = rhs;
    }

    TextureMaterialInstance &TextureMaterialInstance::operator=(TextureMaterialInstance const &rhs)
    {
        if (this != &rhs)
        {
            *this = rhs;
        }
        return *this;
    }

    // Methods

    void TextureMaterialInstance::Bind()
    {
        m_Texture->Bind();
    }

    void TextureMaterialInstance::Unbind()
    {
        m_Texture->Unbind();
    }

    // Getters and setters

    void TextureMaterialInstance::SetLightDirection(glm::vec3 LightDirection)
    {
        m_LightDirection = LightDirection;
    }

    void TextureMaterialInstance::SetViewProjection(glm::mat4 ViewProjection)
    {
        m_ViewProjection = ViewProjection;
    }

    void TextureMaterialInstance::SetRot(glm::mat4 Rot)
    {
        m_Rot = Rot;
    }

    void TextureMaterialInstance::SetModel(glm::mat4 Model)
    {
        m_Model = Model;
    }

    glm::vec3 TextureMaterialInstance::GetLightDirection()
    {
        return m_LightDirection;
    }

    glm::mat4 TextureMaterialInstance::GetViewProjection()
    {
        return m_ViewProjection;
    }

    glm::mat4 TextureMaterialInstance::GetRot()
    {
        return m_Rot;
    }

    glm::mat4 TextureMaterialInstance::GetModel()
    {
        return m_Model;
    }

}