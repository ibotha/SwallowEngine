#include "swpch.hpp"
#include "RenderCommand.hpp"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Swallow {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}