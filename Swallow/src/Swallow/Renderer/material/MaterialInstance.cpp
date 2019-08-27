/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MaterialInstance.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 14:09:14 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/27 10:59:52 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
