#include "swpch.hpp"
#include "Text.hpp"
#include "Primatives.hpp"
#include "Renderer.hpp"
#include "Swallow/Renderer/material/CharMaterial.hpp"
#include "material/CharMaterialInstance.hpp"

namespace Swallow
{
    Text::Text()
    {

    }

    void Text::Draw()
    {
        for (auto c : m_Quads)
        {
            Renderer::Submit(c);
        }
    }

    void Text::Recalculate()
    {
        m_Quads.empty();
        for(auto c : m_Text)
        {
            m_Quads.push_back(Primatives::Quad());
            m_Quads.back()->GetTransform()->SetPosition(m_Pos);
            m_Quads.back()->GetTransform()->SetScale(glm::vec3(1.0f));
            m_Quads.back()->GetTransform()->Recalculate();
            Ref<CharMaterialInstance> mat = CharMaterial::Create();
            mat->SetChar(c);
            m_Quads.back()->SetMaterial(mat);
        }
    }
}