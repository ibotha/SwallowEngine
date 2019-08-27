/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlatColourMaterial.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:52:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/27 15:22:40 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Swallow/Renderer/Renderer.hpp"
#include "FlatColourMaterialInstance.hpp"

namespace Swallow
{
    class FlatColourMaterial
    {
        public:
        //     FlatColourMaterial();
        //     FlatColourMaterial(FlatColourMaterial const &rhs);
        //     FlatColourMaterial &operator=(FlatColourMaterial const &rhs);
        //     ~FlatColourMaterial();
            static Ref<FlatColourMaterialInstance> Create(const std::string &flatColourShaderPath, const std::string &textureShaderPath);
    };
}