#pragma once

#include <swpch.hpp>
#include <Swallow/Core/Core.hpp>
#include <Swallow/Events/Event.hpp>

namespace Swallow {

	struct WindowProps {
		std::string Title;
		uint32_t Width, Height;
		WindowProps(const std::string& title,
			uint32_t width = 1260,
			uint32_t height = 640)
			:Title(title), Width(width), Height(height)
		{
		}
	};

	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual const char* GetClipboardText(void* user_data) = 0;
		virtual void SetClipboardText(void* user_data, const char* text) = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props);
	};
}