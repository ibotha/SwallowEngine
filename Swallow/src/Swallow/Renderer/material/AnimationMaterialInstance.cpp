#include "swpch.hpp"
#include "AnimationMaterialInstance.hpp"

namespace Swallow {

    // Coplien form requirements and other constructors

    AnimationMaterialInstance::AnimationMaterialInstance()
    {
    }

    AnimationMaterialInstance::AnimationMaterialInstance(Ref<Shader> shader)//:m_Colour(0.0f)
    {
		m_Shader = shader;
    }

    AnimationMaterialInstance::AnimationMaterialInstance(Ref<Shader> shader, Ref<Texture2D> texture)//:m_Colour(0.0f)
    {
		m_Shader = shader;
        m_Texture = texture;
    }

    AnimationMaterialInstance::AnimationMaterialInstance(AnimationMaterialInstance const &rhs)
    {
        *this = rhs;
    }

    AnimationMaterialInstance &AnimationMaterialInstance::operator=(AnimationMaterialInstance const &rhs)
    {
        if (this != &rhs)
        {
            *this = rhs;
        }
        return *this;
    }

    AnimationMaterialInstance::~AnimationMaterialInstance()
    {

    }

    // Methods

    void AnimationMaterialInstance::Bind()
    {
        m_Shader->Bind();

        if (m_Texture != nullptr)
            m_Texture->Bind();
        else
            std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat1("u_Colour", m_Colour);
    
        std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat1("u_Anim", u_Anim);
    }

    void AnimationMaterialInstance::Unbind()
    {
        m_Shader->Unbind();
    }
}