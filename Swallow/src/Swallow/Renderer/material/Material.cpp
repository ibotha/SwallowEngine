/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 14:09:14 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/23 14:36:07 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swpch.h"
#include "Material.hpp"

MaterialInstance::MaterialInstance()
{

}

MaterialInstance::MaterialInstance(const char *path)
{
    
}

MaterialInstance::MaterialInstance(MaterialInstance const &rhs)
{
    *this = rhs;
}

MaterialInstance &MaterialInstance::operator=(MaterialInstance const &rhs)
{
    if (this != &rhs)
    {
        *this = rhs;
    }
    return *this;
}

MaterialInstance::~MaterialInstance()
{
    
}

void MaterialInstance::Bind()
{
    m_shader.use();
}