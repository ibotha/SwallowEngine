#pragma once

#include "Swallow/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Swallow {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		OpenGLContext(const OpenGLContext &rhs) = default;
		OpenGLContext &operator=(const OpenGLContext &rhs) = default;
		GLFWwindow* m_WindowHandle;
	};
}