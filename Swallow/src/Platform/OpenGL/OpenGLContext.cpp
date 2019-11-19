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
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}