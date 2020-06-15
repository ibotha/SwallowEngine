#include <swpch.hpp>
#include "Framebuffer.h"

#include <Platform/OpenGL/OpenGLFramebuffer.h>
#include <Swallow/Renderer/Renderer.hpp>

namespace Swallow {
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: SW_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(spec);
		}
		SW_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}