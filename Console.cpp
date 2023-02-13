#include "Console.hpp"
#include "Mouse.hpp"
#include "WindowsException.hpp"


namespace Input {

	Console::Console(Color mouseEnterColor, Color mouseLeaveColor) : 
		m_enterColor(mouseEnterColor),
		m_leaveColor(mouseLeaveColor)
	{
		m_window = GetConsoleWindow();
		THROW_IF_FAILED(m_window);
		m_hstdin = GetStdHandle(STD_INPUT_HANDLE);
		THROW_IF_FAILED(m_hstdin);
		m_hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		THROW_IF_FAILED(m_hstdout);
		updateCursorStatus();
	
	}

	void Console::showUnderscore(bool flag) const {
		CONSOLE_CURSOR_INFO cursorInfo;
		THROW_IF_FAILED(GetConsoleCursorInfo(m_hstdout, &cursorInfo));
		cursorInfo.bVisible = flag;
		THROW_IF_FAILED(SetConsoleCursorInfo(m_hstdout, &cursorInfo));
	}

	void Console::setTextColor(Color color) const {
		THROW_IF_FAILED(SetConsoleTextAttribute(m_hstdout, static_cast<WORD>(color)));
		THROW_IF_FAILED(FlushConsoleInputBuffer(m_hstdin));
	}

	void Console::clear() const {
		COORD coord{ 0, 0 };
		THROW_IF_FAILED(SetConsoleCursorPosition(m_hstdout, coord));
	}

	Rect Console::getWindowRect() const {
		Rect rect;
		THROW_IF_FAILED(GetWindowRect(m_window, &rect));
		return rect;
	}

	void Console::updateCursorStatus() {
		const auto rect = getWindowRect();
		const auto position = Input::Mouse::getPosition();
		const auto fits = PtInRect(&rect, position);

		if (fits && !m_isCursorInWindow) {
			m_isCursorInWindow = true;
			onMouseEnter(position);
		}
		else if (!fits && m_isCursorInWindow) {
			m_isCursorInWindow = false;
			onMouseLeave(position);
		}
	}

	void Console::onMouseEnter(const Point& point) const {
		m_startTime = std::chrono::system_clock::now();
		std::stringstream ss;
		ss << "Mouse entered the console at (" << point.x << ", " << point.y << ")";
		events.notify("onMouseEnter", ss.str());
		setTextColor(m_enterColor);
	}

	void Console::onMouseLeave(const Point& point) const {
		const auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_startTime).count();
		std::stringstream ss;
		ss << "Mouse left the console after " << elapsedTime << "ms at (" << point.x << ", " << point.y << ")\n";
		events.notify("onMouseLeave", ss.str());
		setTextColor(m_leaveColor);
	}

	void Console::reset() const {
		system("cls");
		showUnderscore(true);
		setTextColor(Input::Console::Color::White);
	}
}