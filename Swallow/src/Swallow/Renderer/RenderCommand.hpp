#pragma once

#include "RendererAPI.hpp"

namespace Swallow {

	class RenderCommand
	{
	public:
		inline static void Init() {SW_PROFILE_FUNCTION(); s_RendererAPI->Init(); }
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { SW_PROFILE_FUNCTION();  s_RendererAPI->SetViewport(x, y, width, height); }
		inline static void Clear() { SW_PROFILE_FUNCTION();  s_RendererAPI->Clear(); }
		inline static void ClearColour() { SW_PROFILE_FUNCTION();  s_RendererAPI->ClearColour(); }
		inline static void ClearDepth() { SW_PROFILE_FUNCTION();  s_RendererAPI->ClearDepth(); }
		inline static void SetClearColor(const glm::vec4& color) { SW_PROFILE_FUNCTION();  s_RendererAPI->SetClearColor(color); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { SW_PROFILE_FUNCTION();  s_RendererAPI->DrawIndexed(vertexArray); }
	private:
		static RendererAPI* s_RendererAPI;
	};

}