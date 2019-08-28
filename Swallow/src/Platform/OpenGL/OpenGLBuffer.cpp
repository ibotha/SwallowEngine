#include "swpch.hpp"
#include "OpenGLBuffer.hpp"

#include <glad/glad.h>

namespace Swallow {

	#pragma region VertexBuffer

	OpenGLVertexBuffer::OpenGLVertexBuffer(void * vertices, uint32_t size)
	{
#ifdef MODERN_GL
		glCreateBuffers(1, &m_RendererID);
#else
		glGenBuffers(1, &m_RendererID);
#endif
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout & layout)
	{
		m_Layout = layout;
	}

	BufferLayout const & OpenGLVertexBuffer::GetLayout() const
	{
		return m_Layout;
	}

	#pragma endregion

	#pragma region IndexBuffer

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t * indices, uint32_t count)
		:m_Count(count)
	{
#ifdef MODERN_GL
		glCreateBuffers(1, &m_RendererID);
#else
		glGenBuffers(1, &m_RendererID);
#endif
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	#pragma endregion

}