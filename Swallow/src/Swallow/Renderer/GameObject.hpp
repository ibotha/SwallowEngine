#pragma once
#include "Transform.hpp"
#include "VertexArray.hpp"

namespace Swallow {

    class GameObject
    {
    public:
        GameObject();
        GameObject(Transform transform);
        GameObject &operator=(const GameObject&) = default;
        GameObject(const GameObject&) = default;

        void SetTransform(Ref<Transform> transform) { m_Transform = transform; }
        void SetVertexArray(Ref<VertexArray> VA) { m_VertexArray = VA; }
        //void SetMaterial(Ref<Material> &material) { m_Material = material; }

		inline Ref<Transform> GetTransform() { return m_Transform; }
		inline  Ref<VertexArray> &GetVertexArray() { return m_VertexArray; }
        //const Material &GetMaterial() const { return m_Material; }

        virtual ~GameObject() = default;
        
        //void SetMaterial(Ref<Material> &material);

    private:
        Ref<Transform> m_Transform;
        Ref<VertexArray> m_VertexArray;
        //Material m_Material;
    };
}