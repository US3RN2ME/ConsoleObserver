#ifndef WINDOWS_EXCEPTION_HPP
#define WINDOWS_EXCEPTION_HPP

#include "framework.hpp"
#include "windows.hpp"


namespace Input {
	class WindowsException : public std::exception {
	public:
		WindowsException(long errorCode) noexcept : 
			m_errorCode(errorCode),
			m_msg(getMessageText(errorCode))
		{}

		char const* what() const noexcept override {
			return m_msg.c_str();
		}

		long errorCode() const noexcept {
			return m_errorCode;
		}

		static std::string getMessageText(long errorCode) noexcept {
			LPSTR errorText = nullptr;

			FormatMessageA(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
				nullptr,
				errorCode,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPSTR)&errorText,
				0,
				nullptr
			);

			if (errorText) {
				std::string m_msg = errorText;
				LocalFree(errorText);
				return m_msg;
			}
			return "Unknown exception";
		}

	private:
		long m_errorCode;
		std::string m_msg;
	};
}

#define THROW_IF_FAILED(expression)	\
	if(!(expression)) throw WindowsException(GetLastError());


#endif // !WINDOWS_EXCEPTION_HPP
