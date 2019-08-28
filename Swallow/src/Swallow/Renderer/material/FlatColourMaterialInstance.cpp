/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlatColourMaterialInstance.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:35:29 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 16:07:05 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swpch.hpp"
#include "FlatColourMaterialInstance.hpp"

namespace Swallow {

    // Coplien form requirements and other constructors

    FlatColourMaterialInstance::FlatColourMaterialInstance()
    {
    }

    FlatColourMaterialInstance::FlatColourMaterialInstance(Ref<Shader> shader)
		:m_Colour(0.0f)
    {
		m_Shader = shader;
    }

    FlatColourMaterialInstance::FlatColourMaterialInstance(FlatColourMaterialInstance const &rhs)
    {
        *this = rhs;
    }

    FlatColourMaterialInstance &FlatColourMaterialInstance::operator=(FlatColourMaterialInstance const &rhs)
    {
        if (this != &rhs)
        {
            *this = rhs;
        }
        return *this;
    }

    FlatColourMaterialInstance::~FlatColourMaterialInstance()
    {

    }

    // Methods

    void FlatColourMaterialInstance::Bind()
    {
        m_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_Colour);
    }

    void FlatColourMaterialInstance::Unbind()
    {
        m_Shader->Unbind();
    }
}