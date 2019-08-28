/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlatColourMaterialInstance.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:35:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/27 16:12:24 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "MaterialInstance.hpp"

namespace Swallow {

    class FlatColourMaterialInstance: public MaterialInstance
    {
        public:
            FlatColourMaterialInstance();
            FlatColourMaterialInstance(const std::string &flatColourShaderPath, const std::string &textureShaderPath);
            FlatColourMaterialInstance(FlatColourMaterialInstance const &rhs);
            FlatColourMaterialInstance &operator=(FlatColourMaterialInstance const &rhs);
            ~FlatColourMaterialInstance();

            void Bind();
            void Unbind();
            void SetUniform(std::string const &name, glm::vec2 value);
            void SetUniform(std::string const &name, glm::vec3 value);
            void SetUniform(std::string const &name, glm::vec4 value);
            void SetUniform(std::string const &name, glm::mat4 value);
            void SetColour(const glm::vec4 &colour);
            void SetLightDirection(const glm::vec3 &lightDirection);
            void SetRot(const glm::mat4 &rot);

            Ref<OpenGLShader> GetFlatColourShader();
            glm::vec4 GetColour();
            glm::vec3 GetLightDirection();
            glm::mat4 GetRot();
        private:
            glm::vec4 m_Colour;
            glm::vec3 m_LightDirection;
            glm::mat4 m_Rot;
            Ref<Shader> m_FlatColourShader;
            Ref<Shader> m_TextureShader;
            Ref<Texture2D> m_Texture;
    };
}