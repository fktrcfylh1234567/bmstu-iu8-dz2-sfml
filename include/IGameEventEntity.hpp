//
// Created by fktrc on 27.04.19.
//

#ifndef GAME_IGAMEEVENTENTITY_HPP
#define GAME_IGAMEEVENTENTITY_HPP

#include <IGameEvent.hpp>

class IGameEventEntity : public IGameEvent {
public:
    virtual size_t getActionId() const override  = 0;
    virtual size_t getEntityId() const  = 0;
    virtual size_t getValue() const  = 0;
};

#endif //GAME_IGAMEEVENTENTITY_HPP
