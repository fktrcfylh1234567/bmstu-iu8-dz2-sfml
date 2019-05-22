//
// Created by fktrc on 23.04.19.
//

#ifndef GAME_IEVENT_HPP
#define GAME_IEVENT_HPP

class IEvent {
public:
    virtual size_t getEventId() const = 0;
};

#endif //GAME_IEVENT_HPP
