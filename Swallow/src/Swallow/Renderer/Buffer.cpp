#include "swpch.hpp"
#include "Buffer.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLBuffer.hpp"

namespace Swallow {

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case Swallow::ShaderDataType::Float: return 4;
			case Swallow::ShaderDataType::Float2: return 4 * 2;
			case Swallow::ShaderDataType::Float3: return 4 * 3;
			case Swallow::ShaderDataType::Float4: return 4 * 4;
			case Swallow::ShaderDataType::Mat3: return 4 * 3 * 3;
			case Swallow::ShaderDataType::Mat4: return 4 * 4 * 4;
			case Swallow::ShaderDataType::Int: return 4;
			case Swallow::ShaderDataType::Int2: return 4 * 2;
			case Swallow::ShaderDataType::Int3: return 4 * 3;
			case Swallow::ShaderDataType::Int4: return 4 * 4;
			case Swallow::ShaderDataType::Bool: return 1;
		default:
			break;
		}
		SW_CORE_ASSERT(false, "Unknown Data Shader Data Type");
		return 0;
	}

	BufferElement::BufferElement(ShaderDataType type, const std::string &name, bool normalized)
	:Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
	{}


	BufferLayout::BufferLayout(std::initializer_list<BufferElement> const &elements)
		:m_Elements(elements)
	{
		CalculateOffsetsAndStride();
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		m_Stride = 0;
		for (auto&  e : m_Elements)
		{
			e.Offset = m_Stride;
			m_Stride += e.Size;
		}
	}

	Ref<VertexBuffer> VertexBuffer::Create(void * vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		default:
			break;
		}
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t * indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		default:
			break;
		}
		return nullptr;
	}

}