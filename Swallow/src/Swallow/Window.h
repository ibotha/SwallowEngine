#pragma once

#include "swpch.h"
#include "Swallow/Core.h"
#include "Swallow/Events/Event.h"

namespace Swallow {

	struct WindowProps {
		std::string Title;
		unsigned int Width, Height;
		WindowProps(const std::string& title = "Swallow Engine",
			unsigned int width = 1200,
			unsigned int height = 720)
			:Title(title), Width(width), Height(height)
		{
		}
	};

	class SWALLOW_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual const char* GetClipboardText(void* user_data) = 0;
		virtual void SetClipboardText(void* user_data, const char* text) = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;


		static Window* Create(const WindowProps& props = WindowProps());
	};
}