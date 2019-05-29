#pragma once

#include "Core.h"

namespace Swallow {
	class Input {
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

	protected:
		inline virtual bool IsKeyPressedImpl(int keycode) = 0;

		inline virtual bool IsMouseButtonPressedImpl(int button) = 0;
		inline virtual float GetMouseXImpl() = 0;
		inline virtual float GetMouseYImpl() = 0;
		inline virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Input* s_Instance;
	};
}