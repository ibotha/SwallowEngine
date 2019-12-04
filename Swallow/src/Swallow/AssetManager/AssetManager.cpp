#include "swpch.hpp"
#include "AssetManager.hpp"
#include "../Renderer/Buffer.hpp"
#include "../Renderer/VertexArray.hpp"

namespace Swallow {
    
    std::map<std::string, std::map<std::string, Ref<VertexArray>>> AssetManager::Objects;
    std::map<std::string, Swallow::Ref<Texture2D>> AssetManager::Textures;
    size_t AssetManager::iterator;
    size_t AssetManager::delay;
    size_t AssetManager::delayCounter;
    std::string AssetManager::mainMeshName;

    AssetManager::AssetManager()
    {

    }

    void AssetManager::LoadObject(const std::string& name, const std::string& path)
    {
        iterator = 0;
        delay = 7;
        delayCounter = 0;
        mainMeshName = "";
        Assimp::Importer Importer;
        
        const aiScene* pScene = Importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes);
        std::map<std::string, Ref<VertexArray>> VAinfo;
        if (pScene)
        {
            for (unsigned int i = 0; i < pScene->mNumMeshes; i++)
            {
                aiMesh *currentMesh = pScene->mMeshes[i];
                std::string meshName(currentMesh->mName.C_Str());
                Ref<VertexArray> VA = VertexArray::Create();
                float Verteces[currentMesh->mNumVertices * 8];
                uint32_t Indeces[3 * currentMesh->mNumFaces];
                for (size_t j = 0; j < currentMesh->mNumVertices; j++)
                {

                    int offset = j * 8;
                    //Vertex
                    Verteces[offset + 0] = currentMesh->mVertices[j].x;
                    Verteces[offset + 1] = currentMesh->mVertices[j].y;
                    Verteces[offset + 2] = currentMesh->mVertices[j].z;
                    
                    //Normal
                    Verteces[offset + 3] = currentMesh->mNormals[j].x;
                    Verteces[offset + 4] = currentMesh->mNormals[j].y;
                    Verteces[offset + 5] = currentMesh->mNormals[j].z;

                    //UV
                    Verteces[offset + 6] = currentMesh->mTextureCoords[0][j].x;
                    Verteces[offset + 7] = currentMesh->mTextureCoords[0][j].y;
                }

                Ref<VertexBuffer> VB = VertexBuffer::Create(Verteces, sizeof(Verteces));
                VB->SetLayout({
                    { Swallow::ShaderDataType::Float3, "a_Position" },
                    { Swallow::ShaderDataType::Float3, "a_Normal" },
                    { Swallow::ShaderDataType::Float2, "a_TexCoord" },
                });
                VA->AddVertexBuffer(VB);
                
                int offsetIndeces = 0;
                for (size_t k = 0; k < currentMesh->mNumFaces; k++)
                {
                    for (size_t j = 0; j < currentMesh->mFaces[k].mNumIndices; j++)
                    {
                        Indeces[offsetIndeces] = currentMesh->mFaces[k].mIndices[j];
                        offsetIndeces++;
                    }
                }
                
                Ref<IndexBuffer> IB = IndexBuffer::Create(Indeces, sizeof(Indeces) / sizeof(uint32_t));
                VA->SetIndexBuffer(IB);
                VAinfo.insert({ std::make_pair(meshName, VA)});
            }
        }
        else
        {
            SW_CORE_WARN("Loading Mesh Error! {} : {}", name, path);
        }

        Objects.insert(std::make_pair(name, VAinfo));
    }

    void AssetManager::LoadTexture(const std::string& name, const std::string& path, bool flipy)
    {
        Ref<Texture2D> tex = Texture2D::Create(path, flipy);
        Textures.insert(std::make_pair(name, tex));
    }

    void AssetManager::ListObjects()
    {
        for (auto const &pair: Objects)
        {
            SW_CORE_TRACE("{}", pair.first);
        }
    }

    void AssetManager::ListMeshes(const std::string& byName)
    {
        for (auto const &mesh: Objects[byName])
        {
            SW_CORE_TRACE("Size: {}", mesh.first);
        }
    }

    Ref<VertexArray> AssetManager::FetchObject(const std::string& byName, const std::string& meshName)
    {
        return Objects[byName][meshName];
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