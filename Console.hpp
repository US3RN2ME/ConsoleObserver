#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "framework.hpp"
#include "windows.hpp"
#include "EventManager.hpp"


namespace Input {
	class Console {
	public:
		enum class Color : unsigned short {
			Black,
			DarkBlue,
			DarkGreen,
			DarkCyan,
			DarkRed,
			DarkMagenta,
			DarkYellow,
			DarkGray,
			Gray,
			Blue,
			Green,
			Cyan,
			Red,
			Magenta,
			Yellow,
			White,

			Count
		};

	public:
		Console(Color mouseEnterColor = Color::Green, Color mouseLeaveColor = Color::DarkGreen);

		void showUnderscore(bool flag) const;

		void setTextColor(Color color) const;

		void clear() const;

		Rect getWindowRect() const;

		void updateCursorStatus();

		void reset() const;

	private:
		void onMouseEnter(const Point& point) const;

		void onMouseLeave(const Point& point) const;

	public:
		Observer::EventManager events;

	private:
		mutable std::chrono::time_point<std::chrono::system_clock> m_startTime ;

	private:
		bool m_isCursorInWindow;
		Color m_enterColor;
		Color m_leaveColor;

	private:
		HWND m_window;
		HANDLE m_hstdout;
		HANDLE m_hstdin;
	};
}

#endif // !CONSOLE_HPP
