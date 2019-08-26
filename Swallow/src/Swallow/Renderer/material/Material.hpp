/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 14:09:25 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/23 14:35:35 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Shader.hpp"
#include <functional>

class FlatColourMaterialInstance
{
    virtual void Bind();

    private:
        glm::vec3 m_Colour;
        std::ref<Shader> m_Shader;

};

class FlatColourMaterial
{
    static std::ref<FlatColourMaterialInstance> Create();
};

class MaterialInstance
{
    public:
        MaterialInstance();
        MaterialInstance(const char *path);
        MaterialInstance(MaterialInstance const &rhs);
        MaterialInstance &operator=(MaterialInstance const &rhs);
        ~MaterialInstance();

        virtual void Bind();
    private:
        std::ref<Shader> m_Shader;
};