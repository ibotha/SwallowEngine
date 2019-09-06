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
        m_Transform = std::make_shared<Transform>();
    }

    void Text::Draw()
    {
        for (auto c : m_Quads)
        {
            if (std::isprint(std::dynamic_pointer_cast<CharMaterialInstance>(c->GetMaterial())->GetChar()))
                Renderer::Submit(c);
        }
    }

    void Text::Recalculate()
    {
        m_Transform->Recalculate();
        m_Quads.empty();
        m_Quads.clear();
        float displacement = 0;
        float ydisplacement = 0;

        Ref<GameObject> object = Primatives::CharQuad();
        for(auto c : m_Text)
        {
            Ref<CharMaterialInstance> mat = CharMaterial::Create();
            mat->SetChar(c);
            mat->SetColour(m_Colour);
            if (mat->CanPrint())
            {
                Ref<GameObject> obj= std::make_shared<GameObject>();
                obj->SetVertexArray(object->GetVertexArray());
                m_Quads.push_back(obj);
                glm::vec4 newPos = m_Transform->GetModelMatrix() *
                (glm::vec4(displacement + mat->GetCharRef()->GetLeft() / SW_FONT_RESOLUTION, ydisplacement + (mat->GetCharRef()->GetHeight() - static_cast<double>(mat->GetCharRef()->GetTop())) / -SW_FONT_RESOLUTION, 0, 1.0f));
                m_Quads.back()->GetTransform()->SetPosition(glm::vec3(newPos.x, newPos.y, newPos.z));
                m_Quads.back()->GetTransform()->SetScale(m_Transform->GetScale() * (glm::vec3(mat->GetCharRef()->GetWidth() / SW_FONT_RESOLUTION, mat->GetCharRef()->GetHeight() / SW_FONT_RESOLUTION, 1.0f)));
                m_Quads.back()->GetTransform()->SetRotation(m_Transform->GetRotation());
                m_Quads.back()->GetTransform()->Recalculate();
                
                displacement += (((mat->GetCharRef()->GetAdvance())) / 8192.0);
                if (c == '\n')
                {
                    ydisplacement -= 1;
                    displacement = 0;
                }

                m_Quads.back()->SetMaterial(mat);
            }
        }
    }
}