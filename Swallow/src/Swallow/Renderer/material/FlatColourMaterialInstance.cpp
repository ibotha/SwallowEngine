/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlatColourMaterialInstance.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:35:29 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/27 16:15:50 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FlatColourMaterialInstance.hpp"

namespace Swallow {

    // Coplien form requirements and other constructors

    FlatColourMaterialInstance::FlatColourMaterialInstance()
    {
        m_FlatColourShader = Shader::CreateFromPath("./assets/shaders/flatColourVertex.vs", "./assets/shaders/flatColourFragment.fs");
        m_TextureShader = Shader::CreateFromPath("./assets/shaders/textureVertex.vs", "./assets/shaders/textureFragment.fs");
    }

    FlatColourMaterialInstance::FlatColourMaterialInstance(const std::string &flatColourShaderPath, const std::string &textureShaderPath)
    {
        std::string vertexPath = flatColourShaderPath + "flatColourVertex.vs";
        std::string fragmentPath = flatColourShaderPath + "flatColourFragment.fs";
        m_FlatColourShader = Shader::CreateFromPath(vertexPath.c_str(), fragmentPath.c_str());
        vertexPath = textureShaderPath + "textureVertex.vs";
        fragmentPath = textureShaderPath + "textureFragment.fs";
        m_TextureShader = Shader::CreateFromPath(vertexPath.c_str(), fragmentPath.c_str());
    }

    FlatColourMaterialInstance::FlatColourMaterialInstance(FlatColourMaterialInstance const &rhs)
    {
        *this = rhs;
    }

    FlatColourMaterialInstance &FlatColourMaterialInstance::operator=(FlatColourMaterialInstance const &rhs)
    {
        if (this != &rhs)
        {
            *this = rhs;
        }
        return *this;
    }

    FlatColourMaterialInstance::~FlatColourMaterialInstance()
    {

    }

    // Methods

    void FlatColourMaterialInstance::Bind()
    {
        m_FlatColourShader->Bind();
    }

    void FlatColourMaterialInstance::Unbind()
    {
        m_FlatColourShader->Unbind();
    }

    // Getters and setters

    void FlatColourMaterialInstance::SetUniform(const std::string &uniform, glm::vec2 value)
    {
        std::dynamic_pointer_cast<OpenGLShader>(m_FlatColourShader)->UploadUniformFloat2(uniform.c_str(), value);
    }

    void FlatColourMaterialInstance::SetUniform(const std::string &uniform, glm::vec3 value)
    {
        std::dynamic_pointer_cast<OpenGLShader>(m_FlatColourShader)->UploadUniformFloat3(uniform.c_str(), value);
    }

    void FlatColourMaterialInstance::SetUniform(const std::string &uniform, glm::vec4 value)
    {
        std::dynamic_pointer_cast<OpenGLShader>(m_FlatColourShader)->UploadUniformFloat4(uniform.c_str(), value);
    }

    void FlatColourMaterialInstance::SetUniform(const std::string &uniform, glm::mat4 value)
    {
        std::dynamic_pointer_cast<OpenGLShader>(m_FlatColourShader)->UploadUniformMat4(uniform.c_str(), value);
    }

    void FlatColourMaterialInstance::SetColour(const glm::vec4 &colour)
    {
        m_Colour = colour;
    }

    void FlatColourMaterialInstance::SetLightDirection(const glm::vec3 &lightDirection)
    {
        m_LightDirection = lightDirection;
    }

    void FlatColourMaterialInstance::SetRot(const glm::mat4 &rot)
    {
        m_Rot = rot;
    }

    glm::vec4 FlatColourMaterialInstance::GetColour()
    {
        return m_Colour;
    }

    glm::vec3 FlatColourMaterialInstance::GetLightDirection()
    {
        return m_LightDirection;
    }

    glm::mat4 FlatColourMaterialInstance::GetRot()
    {
        return m_Rot;
    }

    Ref<OpenGLShader> FlatColourMaterialInstance::GetFlatColourShader()
    {
        return std::dynamic_pointer_cast<OpenGLShader>(m_FlatColourShader);
    }
}