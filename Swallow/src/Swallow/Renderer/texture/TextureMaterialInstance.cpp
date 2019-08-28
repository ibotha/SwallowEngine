/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureMaterialInstance.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:12:58 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 16:59:33 by ppreez           ###   ########.fr       */
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
}