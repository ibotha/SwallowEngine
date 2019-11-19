#pragma once

#include "Swallow/AssetManager/GameObject.hpp"

namespace Swallow
{
    class Text
    {
        public:

            Text();
            inline static Ref<Text> Create() { return std::make_shared<Text>();}
            void Draw();
            void Recalculate();
            
            inline void SetText(const std::string &text) {m_Text = text; }
            inline void SetColour(const glm::vec4 &colour) {m_Colour = colour; }
            inline glm::vec4 &GetColour() { return m_Colour; }
            inline Ref<Transform> GetTransform() {return m_Transform;}
            inline std::string GetString() { return m_Text; }

        private:
            std::string m_Text;
            std::vector<Ref<GameObject>> m_Quads;
            Ref<Transform> m_Transform;
            glm::vec4 m_Colour;
    };
}