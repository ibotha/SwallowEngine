/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlatColourMaterial.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:38:21 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/27 15:21:48 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FlatColourMaterial.hpp"

// FlatColourMaterial::FlatColourMaterial()
// {

// }

// FlatColourMaterial::FlatColourMaterial(FlatColourMaterial const &rhs)
// {
//     *this = rhs;
// }

// FlatColourMaterial &FlatColourMaterial::operator=(FlatColourMaterial const &rhs)
// {
//     if (this != &rhs)
//     {
//         *this = rhs;
//     }
//     return *this;
// }

// FlatColourMaterial::~FlatColourMaterial()
// {

// }

namespace Swallow
{
    Ref<FlatColourMaterialInstance> FlatColourMaterial::Create(const std::string &flatColourShaderPath, const std::string &textureShaderPath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<FlatColourMaterialInstance>(flatColourShaderPath, textureShaderPath);
            default:
                break;
        }
        return nullptr;
    }
}