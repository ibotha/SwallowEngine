#pragma once
#include "Transform.hpp"
#include "../Renderer/VertexArray.hpp"
#include "../Renderer/material/MaterialInstance.hpp"

namespace Swallow {

    class AssetManager
    {
    public:
        AssetManager();
        AssetManager &operator=(const AssetManager&) = default;
        AssetManager(const AssetManager&) = default;

        void LoadObject(std::string name, std::string path);
        void LoadTexture(std::string name, std::string path);
        VertexArray FetchObject(std::string byName);
        Texture2D FetchTexture(std::string byName);

    private:
        struct ObjectInfo
        {
            std::string name;
            Swallow::Ref<VertexArray> VA;
        };

        struct TextureInfo
        {
            std::string name;
            Swallow::Ref<Texture2D> texture;
        };

        ObjectInfo Objects;
        TextureInfo Textures;
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