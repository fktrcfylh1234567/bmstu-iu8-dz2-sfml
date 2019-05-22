//
// Created by fktrc on 23.05.19.
//

#ifndef GAME_EVENTGAMEMODE_HPP
#define GAME_EVENTGAMEMODE_HPP


class EventGameMode : public IEvent {
public:
    EventGameMode(size_t eventId) : eventId(eventId) {}

    size_t getEventId() const override {
        return 0;
    }

private:
    size_t eventId;
};


#endif //GAME_EVENTGAMEMODE_HPP
