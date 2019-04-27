//
// Created by fktrc on 23.04.19.
//

#ifndef GAME_IGAMEINSTANCEACTION_HPP
#define GAME_IGAMEINSTANCEACTION_HPP

#include <IGameEventEntity.hpp>

enum {
    GAME_EVENT_ENTITY_IS_ALIVE_CHANGED = 0,
    GAME_EVENT_ENTITY_HP_CHANGED = 1,
    GAME_EVENT_ENTITY_POSITION_CHANGED = 2
};

class GameEventEntityInstance : public IGameEventEntity {
public:
    GameEventEntityInstance(size_t actionId, size_t entityId, size_t newValue) : actionId(actionId), entityId(entityId),
                                                                                 newValue(newValue) {}

    size_t getActionId() const override {
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
