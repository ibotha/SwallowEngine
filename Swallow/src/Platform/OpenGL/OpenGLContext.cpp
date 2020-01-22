#include "swpch.hpp"
#include "OpenGLContext.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Swallow {

	OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
		:m_WindowHandle(windowHandle)
	{
		SW_CORE_ASSERT(windowHandle, "OpenGL WindowHandle does not exist!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SW_CORE_ASSERT(status, "Could Not Initialize Glad");

		SW_CORE_INFO("OpenGL Info:");
		SW_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		SW_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		SW_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		#ifdef SW_ENABLE_ASSERTS
				int versionMajor;
				int versionMinor;
				glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
				glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

				SW_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "SWALLOW requires at least OpenGL version 4.5!");
		#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}