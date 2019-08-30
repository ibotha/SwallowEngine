#include "swpch.hpp"
#include "AssetManager.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Swallow {
    AssetManager::AssetManager()
    {

    }

    void LoadObject(std::string name, std::string path)
    {
        (void)name;
        (void)path;
    }

    void LoadTexture(std::string name, std::string path)
    {
        (void)name;
        (void)path;
    }

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
}