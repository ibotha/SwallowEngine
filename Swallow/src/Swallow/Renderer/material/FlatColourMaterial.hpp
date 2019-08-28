/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlatColourMaterial.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:52:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 13:36:36 by ibotha           ###   ########.fr       */
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
			static void Init(const std::string &VertexPath, const std::string &FragmentPath);
        //     FlatColourMaterial();
        //     FlatColourMaterial(FlatColourMaterial const &rhs);
        //     FlatColourMaterial &operator=(FlatColourMaterial const &rhs);
        //     ~FlatColourMaterial();
			static Ref<FlatColourMaterialInstance> Create();

		private:
			static Ref<Shader> m_Shader;
    };
}