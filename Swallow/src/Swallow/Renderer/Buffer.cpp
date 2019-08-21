#include "swpch.hpp"
#include "Buffer.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLBuffer.hpp"

namespace Swallow {


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