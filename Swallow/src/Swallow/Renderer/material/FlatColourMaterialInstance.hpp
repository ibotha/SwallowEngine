/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlatColourMaterialInstance.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:35:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 13:32:57 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "MaterialInstance.hpp"

namespace Swallow {

    class FlatColourMaterialInstance: public MaterialInstance
    {
        public:
            FlatColourMaterialInstance(Ref<Shader> shader);
            FlatColourMaterialInstance(FlatColourMaterialInstance const &rhs);
            FlatColourMaterialInstance &operator=(FlatColourMaterialInstance const &rhs);
            ~FlatColourMaterialInstance();

            void Bind();
            void Unbind();
            inline void SetColour(const glm::vec4 &colour) {m_Colour = colour;}

            inline glm::vec4 GetColour() const { return m_Colour; }
        private:
            FlatColourMaterialInstance();
            glm::vec4 m_Colour;
    };
}