/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlatColourMaterial.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:52:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 14:39:57 by ibotha           ###   ########.fr       */
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
			static void Init();
        //     FlatColourMaterial();
        //     FlatColourMaterial(FlatColourMaterial const &rhs);
        //     FlatColourMaterial &operator=(FlatColourMaterial const &rhs);
        //     ~FlatColourMaterial();
			static Ref<FlatColourMaterialInstance> Create();

		private:
			static Ref<Shader> m_Shader;
    };
}