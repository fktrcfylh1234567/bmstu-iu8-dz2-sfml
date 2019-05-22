//
// Created by fktrc on 23.04.19.
//

#ifndef GAME_IGAMEINSTANCEACTION_HPP
#define GAME_IGAMEINSTANCEACTION_HPP

#include <IEventEntity.hpp>

class EventEntityInstance : public IEventEntity {
public:
    EventEntityInstance(size_t actionId, size_t entityId, size_t newValue) :
            actionId(actionId), entityId(entityId), newValue(newValue) {}

    size_t getEventId() const override {
        return actionId;
    }

    size_t getEntityId() const override {
        return entityId;
    }

    size_t getValue() const override {
        return newValue;
    }

private:
    size_t actionId;
    size_t entityId;
    size_t newValue;
};

#endif //GAME_IGAMEINSTANCEACTION_HPP
