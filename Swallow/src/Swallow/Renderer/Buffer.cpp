#include "swpch.hpp"
#include "Buffer.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLBuffer.hpp"

namespace Swallow {

	BufferElement::BufferElement(ShaderDataType type, const std::string &name, bool normalized)
	:Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
	{
	}


	BufferLayout::BufferLayout(std::initializer_list<BufferElement> const &elements)
		:m_Elements(elements)
	{
		SW_PROFILE_FUNCTION();
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
		SW_PROFILE_FUNCTION();
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
		default:
			break;
		}
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t * indices, uint32_t count)
	{
		SW_PROFILE_FUNCTION();
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, count);
		default:
			break;
		}
		return nullptr;
	}

}