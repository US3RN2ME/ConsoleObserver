#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "Console.hpp"
#include "LoggingListener.hpp"
#include "WindowsException.hpp"


int main() {
	const auto text = "Hello World!";

	const auto info = "\n--Move mouse outside or inside the console to change the text color"
					  "\n--Press Escape to finish"
					  "\n--Check mouse.log file";

	const auto exitMsg = "Good luck!";
	
	const auto mouseEnterColor = Input::Console::Color::Yellow;
	const auto mouseLeaveColor = Input::Console::Color::DarkYellow;

	const auto delay = 35;

	try {
		const auto logger  = std::make_shared<Observer::LoggingListener>("mouse.log");
		const auto console = std::make_unique<Input::Console>(mouseEnterColor, mouseLeaveColor);
		console->showUnderscore(false);
		console->events.subscribe("onMouseEnter", logger);
		console->events.subscribe("onMouseLeave", logger);

		while (true) {
			std::cout << text << std::endl;
			std::cout << info << std::endl;

			console->clear();

			Sleep(delay);

			console->updateCursorStatus();

			if (Input::Keyboard::isKeyPressed(Input::Keyboard::Key::Escape)) {
				console->reset();
				std::cout << exitMsg << std::endl;
				break;
			}
		}
	}
	catch (const Input::WindowsException& ex) {
		std::stringstream ss;
		ss << "Error: " << ex.what() << '\n' << "Code: " << ex.errorCode();
		MessageBoxA(GetConsoleWindow(), ss.str().c_str(), "WindowsException", MB_OK);
	}
	catch (const std::exception& ex) {
		MessageBoxA(GetConsoleWindow(), ex.what(), "Exception", MB_OK);
	}
}