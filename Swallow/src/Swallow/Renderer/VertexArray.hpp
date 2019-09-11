#pragma once

#include "Buffer.hpp"

namespace Swallow {
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}
		VertexArray();
		VertexArray(const VertexArray&);
		VertexArray &operator=(const VertexArray&);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual std::vector<Ref<VertexBuffer>>& GetVertexBuffers() = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};
}