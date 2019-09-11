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
        std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat1("u_Colour", m_Colour);
        std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat1("u_Anim", u_Anim);
    }

    void AnimationMaterialInstance::Unbind()
    {
        m_Shader->Unbind();
    }
}