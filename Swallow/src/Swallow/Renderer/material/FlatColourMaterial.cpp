/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlatColourMaterial.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:38:21 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/05 13:13:04 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swpch.hpp"
#include "FlatColourMaterial.hpp"

namespace Swallow
{

	Ref<Shader> FlatColourMaterial::m_Shader;

	void FlatColourMaterial::Init()
	{
		m_Shader = Shader::Create("assets/shaders/FlatColour.glsl");
	}

    Ref<FlatColourMaterialInstance> FlatColourMaterial::Create()
    {
		return std::make_shared<FlatColourMaterialInstance>(m_Shader);
    }
}