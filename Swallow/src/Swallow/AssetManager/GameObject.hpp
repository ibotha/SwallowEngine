#pragma once
#include "Transform.hpp"
#include "../Renderer/VertexArray.hpp"
#include "../Renderer/material/MaterialInstance.hpp"

namespace Swallow {

    class GameObject
    {
    public:
        GameObject();
        GameObject(Transform transform);
        GameObject &operator=(const GameObject&) = default;
        GameObject(const GameObject&) = default;

        inline void SetTransform(Ref<Transform> transform) { m_Transform = transform; }
        inline void SetVertexArray(Ref<VertexArray> VA) { m_VertexArray = VA; }
        inline void SetMaterial(Ref<MaterialInstance> material) { m_Material = material; }

		inline Ref<Transform> GetTransform() { return m_Transform; }
		inline Ref<VertexArray> GetVertexArray() { return m_VertexArray; }
        inline Ref<MaterialInstance> GetMaterial() { return m_Material; }

        virtual ~GameObject() = default;
        
        //void SetMaterial(Ref<Material> &material);

    private:
        Ref<Transform> m_Transform;
        Ref<VertexArray> m_VertexArray;
        Ref<MaterialInstance> m_Material;
        //Material m_Material;
    };
}