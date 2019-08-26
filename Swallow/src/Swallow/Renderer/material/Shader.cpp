/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 08:18:19 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/22 15:50:17 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Shader.hpp"

Shader::Shader()
{}

Shader::~Shader()
{}

Shader::Shader(const char *vertexpath, const char *fragmentpath)
{
    const char *vShaderCode;
    const char *fShaderCode;
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::stringstream vShaderStream;
    std::stringstream fShaderStream;
    
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexpath);
        fShaderFile.open(fragmentpath);
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure &e) {
        std::cout << "File read exception: " << e.what() << std::endl;
    }
    vShaderCode = vertexCode.c_str();
    fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    compileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    compileErrors(fragment, "FRAGMENT");
    
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    compileErrors(id, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader(Shader const &rhs)
{
    *this = rhs;
}

Shader &Shader::operator=(Shader const &rhs)
{
    if (this != &rhs)
    {
        *this = rhs;
    }
    return *this;
}

void Shader::use() const
{
    glUseProgram(id);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string &name, glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::compileErrors(unsigned int shader, std::string type)
{
    int success;
    char infolog[512];
    
    if (type == "PROGRAM")
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 512, NULL, infolog);
            std::cout << "Program link error: " << infolog << std::endl;
            m_errors = true;
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infolog);
            std::cout << "Shader compile error: " << infolog << std::endl;
            m_errors = true;

        }
    }
    
}