/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureMaterialInstance.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:12:58 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/06 09:32:52 by ppreez           ###   ########.fr       */
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
        m_Shader = shader;
    }

    TextureMaterialInstance::TextureMaterialInstance(Ref<Shader> shader, Ref<Texture2D> texture)
    {
        m_Shader = shader;
        m_Texture = texture;
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
        m_Shader->Bind();
        m_Texture->Bind();
    }

    void TextureMaterialInstance::Unbind()
    {
        m_Shader->Unbind();
    }
}