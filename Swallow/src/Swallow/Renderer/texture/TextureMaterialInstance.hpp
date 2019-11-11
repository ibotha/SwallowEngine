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

#include "Swallow/Renderer/material/MaterialInstance.hpp"

namespace Swallow {

    class TextureMaterialInstance: public MaterialInstance
    {
        public:
            TextureMaterialInstance(Ref<Shader> shader);
            TextureMaterialInstance(Ref<Shader> shader, Ref<Texture2D> texture);
            TextureMaterialInstance(TextureMaterialInstance const &rhs);
            TextureMaterialInstance &operator=(TextureMaterialInstance const &rhs);
            ~TextureMaterialInstance() = default;

            void Bind();
            void Unbind();



            inline void SetTexture(Ref<Texture2D> texture) { m_Texture = texture;}
            inline Ref<Texture2D> GetTextureImage() { return m_Texture;}
        private:
            TextureMaterialInstance();
            Ref<Texture2D> m_Texture;
    };
}
