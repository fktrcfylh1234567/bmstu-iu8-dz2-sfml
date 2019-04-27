//
// Created by fktrc on 23.04.19.
//

#ifndef GAME_IGAMEEVENT_HPP
#define GAME_IGAMEEVENT_HPP

class IGameEvent {
public:
    virtual size_t getActionId() const = 0;
};

#endif //GAME_IGAMEEVENT_HPP
