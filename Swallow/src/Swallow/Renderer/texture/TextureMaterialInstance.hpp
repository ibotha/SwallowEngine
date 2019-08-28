/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureMaterialInstance.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:09:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 16:56:44 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "TextureInstance.hpp"

namespace Swallow {

    class TextureMaterialInstance: public TextureInstance
    {
        public:
            TextureMaterialInstance(Ref<Shader> shader);
            TextureMaterialInstance(Ref<Shader> shader, Ref<Texture2D> texture);
            TextureMaterialInstance &operator=(TextureMaterialInstance const &rhs);
            ~TextureMaterialInstance();

            void Bind();
            void Unbind();
        private:
            TextureMaterialInstance();
    };
}
