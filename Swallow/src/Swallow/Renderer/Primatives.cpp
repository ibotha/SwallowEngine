#include "swpch.hpp"
#include "Buffer.hpp"
#include "GameObject.hpp"
#include "VertexArray.hpp"
#include "Primatives.hpp"

namespace Swallow {

    Ref<GameObject> Primatives::Cube()
    {
        Ref<GameObject> ret = std::make_shared<GameObject>();
        Ref<VertexArray> VA = VertexArray::Create();
        float Verteces[8 * 8] = {
            -0.5f,  0.5f,  0.5f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f
        };
        
        Ref<VertexBuffer> VB = VertexBuffer::Create(Verteces, sizeof(Verteces));
        VB->SetLayout({
            { Swallow::ShaderDataType::Float3, "a_Position" },
            { Swallow::ShaderDataType::Float3, "a_Normal" },
            { Swallow::ShaderDataType::Float2, "a_TexCoord" },
        });
        VA->AddVertexBuffer(VB);
        
        uint32_t Indeces[3 * 12]= {
            //North 0 1 2 3
            0, 1, 2,
            2, 3, 0,
            //East 1 5 6 2
            1, 5, 6,
            6, 2, 1,
            //South 7 6 5 4
            7, 6, 5,
            5, 4, 7,
            //West 0 3 7 4
            0, 3, 7,
            7, 4, 0,
            //Top 0 4 5 1
            0, 4, 5,
            5, 1, 0,
            //Bottom 7 3 2 6
            7, 3, 2,
            2, 6, 7
        };

        Ref<IndexBuffer> IB = IndexBuffer::Create(Indeces, sizeof(Indeces) / sizeof(uint32_t));
        VA->SetIndexBuffer(IB);
        ret->SetVertexArray(VA);
        return (ret);
    }

    Ref<GameObject> Primatives::Quad()
    {
        Ref<GameObject> ret = std::make_shared<GameObject>();
        Ref<VertexArray> VA = VertexArray::Create();
		float Verteces[4 * 9] = {
			-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 
			 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
		};
        
        Ref<VertexBuffer> VB = VertexBuffer::Create(Verteces, sizeof(Verteces));
        VB->SetLayout({
            { Swallow::ShaderDataType::Float3, "a_Position" },
            { Swallow::ShaderDataType::Float3, "a_Normal" },
            { Swallow::ShaderDataType::Float2, "a_TexCoord" },
        });
        VA->AddVertexBuffer(VB);
        
		uint32_t Indeces[3 * 2] = {
			0, 1, 2,
			2, 3, 0
		};

        Ref<IndexBuffer> IB = IndexBuffer::Create(Indeces, sizeof(Indeces) / sizeof(uint32_t));
        VA->SetIndexBuffer(IB);
        ret->SetVertexArray(VA);
        return (ret);
    }

    Ref<GameObject> Primatives::CharQuad()
    {
        Ref<GameObject> ret = std::make_shared<GameObject>();
        Ref<VertexArray> VA = VertexArray::Create();
		float Verteces[4 * 9] = {
			 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 
			 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 
			 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
		};
        
        Ref<VertexBuffer> VB = VertexBuffer::Create(Verteces, sizeof(Verteces));
        VB->SetLayout({
            { Swallow::ShaderDataType::Float3, "a_Position" },
            { Swallow::ShaderDataType::Float3, "a_Normal" },
            { Swallow::ShaderDataType::Float2, "a_TexCoord" },
        });
        VA->AddVertexBuffer(VB);
        
		uint32_t Indeces[3 * 2] = {
			0, 1, 2,
			2, 3, 0
		};

        Ref<IndexBuffer> IB = IndexBuffer::Create(Indeces, sizeof(Indeces) / sizeof(uint32_t));
        VA->SetIndexBuffer(IB);
        ret->SetVertexArray(VA);
        return (ret);
    }
}