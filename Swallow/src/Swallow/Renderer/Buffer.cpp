#include "swpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

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

	VertexBuffer * VertexBuffer::Create(void * vertices, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None:
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		default:
			break;
		}
		return nullptr;
	}

	IndexBuffer * IndexBuffer::Create(uint32_t * indices, uint32_t count)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None:
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		default:
			break;
		}
		return nullptr;
	}

}