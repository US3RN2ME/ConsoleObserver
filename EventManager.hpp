#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "IEventListener.hpp"


namespace Observer {
    class EventManager {
    public:
        void subscribe(const std::string& e, std::shared_ptr<IEventListener> observer) {
            m_observers.emplace(e, observer);
        }

        void unsubscribe(const std::string& e) {
            m_observers.erase(e);
        }

        void notify(const std::string& key, const std::string& message) const {
            for (auto& [k, val] : m_observers) {
                if (key == k) {
                    val->update(message);
                    break;
                }
            }
        }

    private:
        std::map<std::string, std::shared_ptr<IEventListener>> m_observers{};
    };
}
#endif // !EVENT_MANAGER_HPP