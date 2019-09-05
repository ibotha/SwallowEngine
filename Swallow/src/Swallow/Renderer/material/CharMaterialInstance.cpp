#include "swpch.hpp"
#include "CharMaterialInstance.hpp"

namespace Swallow
{
    CharMaterialInstance::CharMaterialInstance(Ref<Shader> shader, Ref<std::map<unsigned char, Ref<Character>>> characters)
    {
        m_Shader = shader;
        m_Chars = characters;
        m_Char = 'A';
    }

    void CharMaterialInstance::Bind()
    {
        (*m_Chars)[m_Char]->Bind();
        m_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_Colour);
    }

    void CharMaterialInstance::Unbind()
    {
        m_Shader->Unbind();
    }
}