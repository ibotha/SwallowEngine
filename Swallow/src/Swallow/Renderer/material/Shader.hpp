/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 08:18:10 by ppreez            #+#    #+#             */
/*   Updated: 2019/08/22 15:52:26 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include "glm.hpp"
#include "GLFW/glfw3.h"

class Shader
{
    public:
        Shader(const char *vertexpath, const char *fragmentpath);
        Shader(Shader const &rhs);
        Shader &operator=(Shader const &rhs);
        ~Shader();
        
        unsigned int id;
        bool m_errors;
        void use() const;
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec2(const std::string &name, float x, float y) const;
        void setMat2(const std::string &name, glm::mat2 &mat) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec3(const std::string &name, glm::vec3 value) const;
        void setMat3(const std::string &name, glm::mat3 &mat) const;
        void setVec4(const std::string &name, float x, float y, float z, float w) const;
        void setMat4(const std::string &name, glm::mat4 &mat) const;

    private:
        Shader();
        void compileErrors(unsigned int shader, std::string type);
        
};