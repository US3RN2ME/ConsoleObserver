#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "windows.hpp"
#include "WindowsException.hpp"


namespace Input {
	struct Mouse {
		enum class Button {
			Left = 1,
			Right = 2,
			Middle = 4,
			X1 = 5,
			X2 = 6,

			Count = 5
		};

		static inline bool isButtonPressed(Button button) noexcept {
			return GetAsyncKeyState(static_cast<int>(button)) & 0x8000;
		}

		static inline Point getPosition() {
			Point point;
			THROW_IF_FAILED(GetCursorPos(&point));
			return point;
		}
	};
}

#endif // !MOUSE_HPP