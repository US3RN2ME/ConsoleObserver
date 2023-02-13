#ifndef IEVENT_LISTENER_HPP
#define IEVENT_LISTENER_HPP


namespace Observer {
    struct IEventListener {
        virtual ~IEventListener() = default;
        virtual void update(const std::string& message) = 0;
    };
}

#endif // !IEVENT_LISTENER_HPP