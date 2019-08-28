/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlatColourMaterial.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:38:21 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 13:42:46 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swpch.hpp"
#include "FlatColourMaterial.hpp"

// FlatColourMaterial::FlatColourMaterial()
// {

// }

// FlatColourMaterial::FlatColourMaterial(FlatColourMaterial const &rhs)
// {
//     *this = rhs;
// }

// FlatColourMaterial &FlatColourMaterial::operator=(FlatColourMaterial const &rhs)
// {
//     if (this != &rhs)
//     {
//         *this = rhs;
//     }
//     return *this;
// }

// FlatColourMaterial::~FlatColourMaterial()
// {

// }

namespace Swallow
{

	Ref<Shader> FlatColourMaterial::m_Shader;

	void FlatColourMaterial::Init(const std::string &VertexPath, const std::string &FragmentPath)
	{
		m_Shader = Shader::CreateFromPath(VertexPath.c_str(), FragmentPath.c_str());
	}

    Ref<FlatColourMaterialInstance> FlatColourMaterial::Create()
    {
		return std::make_shared<FlatColourMaterialInstance>(m_Shader);
    }
}