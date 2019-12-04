#include "swpch.hpp"
#include "WindowsWindow.hpp"
#include "Swallow/Application.hpp"

#include "Swallow/Events/ApplicationEvent.hpp"
#include "Swallow/Events/KeyEvent.hpp"
#include "Swallow/Events/MouseEvent.hpp"

#include "Platform/OpenAL/OpenALContext.hpp"

#include "Platform/OpenGL/OpenGLContext.hpp"
#include <glad/glad.h>

namespace Swallow {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	Swallow::WindowsWindow::WindowsWindow(const WindowProps & props)
	{
		Init(props);
	}

	Swallow::WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void Swallow::WindowsWindow::Init(const WindowProps & props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		if (!s_GLFWInitialized) {
			SW_CORE_INFO("bjkasdbjkadsbjknadsbjk");
			int success = glfwInit();
			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
            #ifdef __APPLE__
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
            #endif
			SW_CORE_ASSERT(success, "Could Not Initialize GLFW");
			glfwSetErrorCallback([](int code, const char *message) {SW_CORE_ASSERT(false, "GLFW Error {0}: {1}", code, message)});

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_GraphicsContext = std::make_unique<OpenGLContext>(m_Window);
		m_GraphicsContext->Init();

		auto m_Device = alcOpenDevice(0);
		m_Audio = alcCreateContext(m_Device, 0);

		m_AudioContext = std::make_unique<OpenALContext>(m_Audio);
		m_AudioContext->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		glfwMakeContextCurrent(m_Window);
		glClearColor(1, 1, 1, 1);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_Window);

		// Set all the necessary callbacks for glfw events
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowsWindow::WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowResizeEvent event(width, height);
			data.Width = width;
			data.Height = height;
			glViewport(0, 0, width, height);
			glScissor(0, 0, width, height);
			data.EventCallback(event);

		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowsWindow::WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			static_cast<void>(scancode);
			static_cast<void>(mods);
			WindowsWindow::WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			Event *event;
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent keyevent(key, 0);
					event = &keyevent;
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent keyevent(key, 1);
					event = &keyevent;
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent keyevent(key);
					event = &keyevent;
					break;
				}
			}
			data.EventCallback(*event);
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int key)
		{
			WindowsWindow::WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(key);

			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			static_cast<void>(mods);
			WindowsWindow::WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS)
			{
				MouseButtonPressedEvent keyevent(button);
				data.EventCallback(keyevent);
			}
			if (action == GLFW_RELEASE)
			{
				MouseButtonReleasedEvent keyevent(button);
				data.EventCallback(keyevent);
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowsWindow::WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowsWindow::WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)x, (float)y);
			data.EventCallback(event);
		});
	}

	void Swallow::WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		alcDestroyContext(m_Audio);
		glfwTerminate();
		s_GLFWInitialized = false;
	}

	void Swallow::WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_GraphicsContext->SwapBuffers();
	}

	inline void * WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}

	void Swallow::WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}

	bool Swallow::WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}