#pragma once
#include "GameObject.hpp" 

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
            inline void SetPos(const glm::vec3 &pos) { m_Pos = pos; }
        private:
            std::string m_Text;
            std::vector<Ref<GameObject>> m_Quads;
            glm::vec3 m_Pos;
    };
}