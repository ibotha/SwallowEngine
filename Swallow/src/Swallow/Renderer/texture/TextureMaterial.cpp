/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureMaterial.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:02:59 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/28 16:55:54 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swpch.hpp"
#include "TextureMaterial.hpp"


namespace Swallow
{
	Ref<Shader> TextureMaterial::m_Shader;

    void TextureMaterial::Init()
    {
        std::string textureVertexSrc = R"(
		#version 330 core
		

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec3 a_Normal;
		layout(location = 2) in vec2 a_TexCoord;

		out vec3 v_Normal;
		out vec2 v_TexCoord;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Rot;
		uniform mat4 u_Model;

		void main() {
			gl_Position = (u_ViewProjection * u_Model) * vec4(a_Position, 1.0);
			v_Normal = normalize(u_Rot * vec4(a_Normal, 0.0)).xyz;
			v_TexCoord = a_TexCoord;
		}
	)";

	std::string textureFragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;
		in vec3 v_Normal;
		in vec2 v_TexCoord;

		uniform vec3 u_LightDirection = vec3(0.3, -1, -0.5);
		uniform sampler2D u_Texture;

		void main() {
			float Light = max(0.0, dot(v_Normal, -normalize(u_LightDirection))) * 0.9 + 0.1;
			color = vec4(texture(u_Texture, v_TexCoord).rgb * Light, 1.0);
		}
	)";
        m_Shader = Shader::Create(textureVertexSrc, textureFragmentSrc);
    }

    Ref<TextureMaterialInstance> TextureMaterial::Create()
    {
        return std::make_shared<TextureMaterialInstance>(m_Shader);
    }
}