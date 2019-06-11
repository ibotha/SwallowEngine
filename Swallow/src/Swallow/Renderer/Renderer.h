#pragma once
#include "Shader.h"
#include "Buffer.h"

namespace Swallow {

	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1,
		DirectX = 2
	};

	class Renderer
	{
	public:
		inline static RendererAPI getAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}