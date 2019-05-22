//
// Created by fktrc on 23.04.19.
//

#ifndef GAME_IEVENT_HPP
#define GAME_IEVENT_HPP

enum gameEventsInstance {
    GAME_EVENT_MATCH_START = 0,
    GAME_EVENT_MATCH_STOP = 1,
    GAME_EVENT_ENTITY_IS_ALIVE_CHANGED = 2,
    GAME_EVENT_ENTITY_POSITION_CHANGED = 3,
    GAME_EVENT_ENTITY_HP_CHANGED = 4
};

class IEvent {
public:
    virtual size_t getEventId() const = 0;
};

#endif //GAME_IEVENT_HPP
