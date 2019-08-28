/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlatColourMaterial.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:38:21 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 14:42:54 by ibotha           ###   ########.fr       */
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

	void FlatColourMaterial::Init()
	{

		std::string sVertexSrc = R"(
			#version 330 core
			

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec3 a_Normal;

			out vec3 v_Normal;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Rot;
			uniform mat4 u_Model;

			void main() {
				gl_Position = (u_ViewProjection * u_Model) * vec4(a_Position, 1.0);
				v_Normal = normalize(u_Rot * vec4(a_Normal, 0.0)).xyz;
			}
		)";

		std::string sFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Normal;

			uniform vec3 u_LightDirection = vec3(0, -1, 0);
			uniform vec4 u_Color = vec4(0.6, 0.1, 0.5, 1.0);

			void main() {
				float v_Light = max(0.0, dot(v_Normal, -normalize(u_LightDirection))) * 0.9 + 0.1;
				color = vec4(u_Color.rgb * v_Light, u_Color.a);
			}
		)";
		m_Shader = Shader::Create(sVertexSrc, sFragmentSrc);
	}

    Ref<FlatColourMaterialInstance> FlatColourMaterial::Create()
    {
		return std::make_shared<FlatColourMaterialInstance>(m_Shader);
    }
}