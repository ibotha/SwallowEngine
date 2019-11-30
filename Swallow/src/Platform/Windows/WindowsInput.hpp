#pragma once

#include <Swallow/Core/Core.hpp>
#include <Swallow/Core/Input.hpp>

namespace Swallow {
	class WindowsInput : public Input {
	public:
		WindowsInput() = default;

	protected:
		WindowsInput(const WindowsInput &rhs) = default;
		WindowsInput &operator=(const WindowsInput &rhs) = default;
		virtual ~WindowsInput() = default;
		virtual inline bool IsKeyPressedImpl(int keycode) override;

		virtual inline bool IsMouseButtonPressedImpl(int button) override;
		inline virtual std::pair<float, float> GetMousePositionImpl() override;
		inline virtual float GetMouseXImpl() override;
		inline virtual float GetMouseYImpl() override;
	};
}