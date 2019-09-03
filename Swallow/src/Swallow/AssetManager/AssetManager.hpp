#pragma once
#include "Transform.hpp"
#include "../Renderer/VertexArray.hpp"
#include "../Renderer/material/MaterialInstance.hpp"

namespace Swallow {

    class AssetManager
    {
    public:
        static void LoadObject(const std::string& name, const std::string& path);
        static void LoadTexture(const std::string& name, const std::string& path);
        static Ref<VertexArray> FetchObject(const std::string& byName);
        static Ref<Texture2D> FetchTexture(const std::string& byName);

    private:
        AssetManager();
        AssetManager &operator=(const AssetManager&) = default;
        AssetManager(const AssetManager&) = default;
        ~AssetManager();
        
        static std::map<std::string, Ref<VertexArray>> Objects;
        static std::map<std::string, Ref<Texture2D>> Textures;
        /*
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
        */
    };
}