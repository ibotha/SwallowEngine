#include "swpch.hpp"
#include "AssetManager.hpp"
#include <assimp/Importer.hpp>
#include <assimp/BaseImporter.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Swallow {
    
    std::map<std::string, Swallow::Ref<VertexArray>> AssetManager::Objects;
    std::map<std::string, Swallow::Ref<Texture2D>> AssetManager::Textures;
    
    AssetManager::AssetManager()
    {
        auto x = Assimp::Importer();
    }

    void AssetManager::LoadObject(const std::string& name, const std::string& path)
    {
        (void)name;
        (void)path;
    }

    void AssetManager::LoadTexture(const std::string& name, const std::string& path)
    {
        (void)name;
        (void)path;
    }

    Ref<VertexArray> AssetManager::FetchObject(const std::string& byName)
    {
        return Objects[byName];
    }

    Ref<Texture2D> AssetManager::FetchTexture(const std::string& byName)
    {
        return Textures[byName];
    }

    /*
    Swallow::VertexArray *FetchObject(std::string byName)
    {
        (void)byName;
        Swallow::VertexArray *blank = nullptr;
        return blank;
    }

    Swallow::Texture2D *FetchTexture(std::string byName)
    {
        (void)byName;
        Swallow::Texture2D *blank = nullptr;
        return blank;
    }
    */
}