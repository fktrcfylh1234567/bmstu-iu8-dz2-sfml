//
// Created by fktrc on 27.04.19.
//

#ifndef GAME_IEVENTENTITY_HPP
#define GAME_IEVENTENTITY_HPP

#include <IEvent.hpp>

class IEventEntity : public IEvent {
public:
    virtual size_t getEventId() const override  = 0;
    virtual size_t getEntityId() const  = 0;
    virtual size_t getValue() const  = 0;
};

#endif //GAME_IEVENTENTITY_HPP
