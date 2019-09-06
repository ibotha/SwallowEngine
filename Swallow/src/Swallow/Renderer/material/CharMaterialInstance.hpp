#pragma once

#include "MaterialInstance.hpp"

namespace Swallow {

    class CharMaterialInstance: public MaterialInstance
    {
        public:
            CharMaterialInstance(Ref<Shader> shader, Ref<std::map<unsigned char, Ref<Character>>> characters);
            CharMaterialInstance(CharMaterialInstance const &rhs) = default;
            CharMaterialInstance &operator=(CharMaterialInstance const &rhs) = default;
            ~CharMaterialInstance() = default;

            virtual void Bind() override;
            virtual void Unbind() override;
            bool CanPrint();
            inline void SetColour(const glm::vec4 &colour) {m_Colour = colour;}
            inline glm::vec4 GetColour() const { return m_Colour; }
            inline void SetChar(char c) {m_Char = c;}
            inline char GetChar() const { return m_Char; }
            inline Ref<Character> GetCharRef() { return (*m_Chars)[m_Char]; }
        private:
            CharMaterialInstance();
            glm::vec4 m_Colour;
            char m_Char;

            Ref<std::map<unsigned char, Ref<Character>>> m_Chars;
    };
}