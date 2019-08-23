#pragma once

#include "RendererAPI.hpp"

namespace Swallow {

	class RenderCommand
	{
	public:
		inline static void Clear() { s_RendererAPI->Clear(); }
		inline static void ClearColour() { s_RendererAPI->ClearColour(); }
		inline static void ClearDepth() { s_RendererAPI->ClearDepth(); }
		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		inline static void SetDepthTest(bool val) { s_RendererAPI->SetDepthTest(val); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }
	private:
		static RendererAPI* s_RendererAPI;
	};

}