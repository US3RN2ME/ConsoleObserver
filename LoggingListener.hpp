#ifndef LOGGING_LISTENER_HPP
#define LOGGING_LISTENER_HPP

#include "IEventListener.hpp"


namespace Observer {
	class LoggingListener : public IEventListener {
	public:
		LoggingListener(const std::string& filename) :
			m_filename(filename)
		{}

		void update(const std::string& message) override {
			std::ofstream ofs(m_filename, std::ios::app);
			ofs << message << std::endl;
		}

	private:
		std::string m_filename;
	};
}


#endif // !LOGGING_LISTENER_HPP