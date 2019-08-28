/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureInstance.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 15:38:36 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 15:50:30 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swpch.hpp"
#include "TextureInstance.hpp"


namespace Swallow {

    TextureInstance::TextureInstance()
    {
        
    }

    TextureInstance::TextureInstance(TextureInstance const &rhs)
    {
        *this = rhs;
    }

    TextureInstance &TextureInstance::operator=(TextureInstance const &rhs)
    {
        if (this != &rhs)
        {
            *this = rhs;
        }
        return *this;
    }

    TextureInstance::~TextureInstance()
    {
        
    }
}