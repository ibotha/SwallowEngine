#include "swpch.h"
#include "WindowsWindow.h"

#include "Swallow/Events/ApplicationEvent.h"
#include "Swallow/Events/KeyEvent.h"
#include "Swallow/Events/MouseEvent.h"

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
		m_Data.EventCallback = NULL;

		SW_CORE_INFO("Creating Window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();

			SW_CORE_ASSERT(success, "Could Not Initialize GLFW");
			glfwSetErrorCallback([](int code, const char *message) {SW_CORE_ASSERT(false, "GLFW Error {0}: {1}", code, message)});

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SW_CORE_ASSERT(status, "Could Not Initialize Glad");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set all the necessary callbacks for glfw events
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowsWindow::WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowResizeEvent event(width, height);
			data.Width = width;
			data.Height = height;
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

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowsWindow::WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			Event *event;
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent keyevent(button);
					event = &keyevent;
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent keyevent(button);
					event = &keyevent;
					break;
				}
			}
			data.EventCallback(*event);
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
	}

	void Swallow::WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
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