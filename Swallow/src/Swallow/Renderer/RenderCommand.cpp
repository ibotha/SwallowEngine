#include "swpch.hpp"
#include "RenderCommand.hpp"
#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Swallow {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}