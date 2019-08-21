#pragma once

#include "Swallow/Core.hpp"
#include "Swallow/Input.hpp"

namespace Swallow {
	class WindowsInput : public Input {
	protected:
		virtual inline bool IsKeyPressedImpl(int keycode) override;

		virtual inline bool IsMouseButtonPressedImpl(int button) override;
		inline virtual std::pair<float, float> GetMousePositionImpl() override;
		inline virtual float GetMouseXImpl() override;
		inline virtual float GetMouseYImpl() override;
	};
}