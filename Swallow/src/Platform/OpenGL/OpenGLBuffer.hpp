#pragma once
#include "Swallow/Renderer/Buffer.hpp"

namespace Swallow {

	#pragma region VertexBuffer

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size, bool dynamic = true);
		OpenGLVertexBuffer(void* vertices, uint32_t size, bool dynamic = false);

		OpenGLVertexBuffer(const OpenGLVertexBuffer &rhs) = default;
		OpenGLVertexBuffer &operator=(const OpenGLVertexBuffer &rhs) = default;
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual void SetLayout(const BufferLayout & layout) override;
		virtual BufferLayout const &GetLayout() const override;

	private:
		RendererID m_RendererID;
		BufferLayout m_Layout;

		// Inherited via VertexBuffer
	};

	#pragma endregion

	#pragma region IndexBuffer

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t *indeces, uint32_t count);
		OpenGLIndexBuffer(const OpenGLIndexBuffer &rhs) = default;
		OpenGLIndexBuffer &operator=(const OpenGLIndexBuffer &rhs) = default;
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		inline virtual uint32_t GetCount() const override { return m_Count; }
	private:
		RendererID m_RendererID;
		uint32_t m_Count;
	};

	#pragma endregion
	
}