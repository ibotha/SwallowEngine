#pragma once

#include "Swallow/Window.h"
#include "Swallow/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Swallow {
	
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		WindowsWindow(const WindowsWindow &rhs) = default;
		WindowsWindow &operator=(const WindowsWindow &rhs) = default;
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		inline const char* GetClipboardText(void* user_data) override { return glfwGetClipboardString((GLFWwindow*)user_data); }
		inline void SetClipboardText(void* user_data, const char* text) override { glfwSetClipboardString((GLFWwindow*)user_data, text); }

		inline void* GetNativeWindow() const override;

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	
		GLFWwindow* m_Window;

		GraphicsContext *m_Context;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	};
}