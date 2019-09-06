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
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat4("textColor", m_Colour);
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformInt1("text", glm::vec1(0));
    }

    void CharMaterialInstance::Unbind()
    {
        m_Shader->Unbind();
    }

    bool CharMaterialInstance::CanPrint()
    {
        if (m_Chars->find(m_Char) == m_Chars->end())
            return false;
        return true;
    }
}