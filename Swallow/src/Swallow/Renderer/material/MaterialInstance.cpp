/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MaterialInstance.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 14:09:14 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 13:26:20 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swpch.hpp"

#include "MaterialInstance.hpp"

namespace Swallow {

    MaterialInstance::MaterialInstance()
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
}
