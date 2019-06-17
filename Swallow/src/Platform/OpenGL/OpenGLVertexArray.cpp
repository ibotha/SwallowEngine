#include "swpch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Swallow {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Swallow::ShaderDataType::Float:	return GL_FLOAT;
		case Swallow::ShaderDataType::Float2:	return GL_FLOAT;
		case Swallow::ShaderDataType::Float3:	return GL_FLOAT;
		case Swallow::ShaderDataType::Float4:	return GL_FLOAT;
		case Swallow::ShaderDataType::Mat3:		return GL_FLOAT;
		case Swallow::ShaderDataType::Mat4:		return GL_FLOAT;
		case Swallow::ShaderDataType::Int:		return GL_INT;
		case Swallow::ShaderDataType::Int2:		return GL_INT;
		case Swallow::ShaderDataType::Int3:		return GL_INT;
		case Swallow::ShaderDataType::Int4:		return GL_INT;
		case Swallow::ShaderDataType::Bool:		return GL_BOOL;
		default:
			break;
		}
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		int i = 0;
		for (const auto &e : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(
				i,
				e.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(e.Type),
				e.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void *)e.Offset);
			i++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
}