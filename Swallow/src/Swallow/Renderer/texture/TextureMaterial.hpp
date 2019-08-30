/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureMaterial.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:03:20 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/30 12:22:58 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Swallow/Renderer/Renderer.hpp"
#include "TextureMaterialInstance.hpp"

namespace Swallow {
    
    class TextureMaterial
    {
        public:
            static void Init();
            static Ref<TextureMaterialInstance> Create();
        private:
            static Ref<Shader> m_Texture;
    };
}
