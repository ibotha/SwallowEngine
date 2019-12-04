#pragma once

#include "Swallow/Renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace Swallow {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext() { SW_CORE_INFO("BYE!"); }
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		OpenGLContext(const OpenGLContext &rhs) = default;
		OpenGLContext &operator=(const OpenGLContext &rhs) = default;
		GLFWwindow* m_WindowHandle;
	};
}