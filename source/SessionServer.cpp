//
// Created by fktrc on 22.05.19.
//

#include "SessionServer.hpp"

void SessionServer::setupMatch(std::string levelName, std::string gameModeName) {
    if (gameRunnimg)
        return;

    match = std::make_unique<Match>();

    size_t gameModeId = 1;

    if (gameModeName == "tdm") {
        gameModeId = 1;
    }

    match->setupGame(levelName, gameModeId);
}

void SessionServer::createLobby() {
    if (gameRunnimg)
        return;

    lobbyOpened = true;
    server.start();
}

void SessionServer::startMatch() {
    if (gameRunnimg)
        return;

    lobbyOpened = false;
    gameRunnimg = true;

    match->run();
    server.closeLobby();

    std::thread([this]() {
        while (true) {
            std::vector<std::shared_ptr<IEvent>> events = match->getGameEvents().wait_and_pop();
            if (events.empty()) {
                break;
            }

            std::string msg = eventsToJSON(events);
            server.sendMessage(msg);
        }
    }).detach();

    match->getGameEvents().wait_and_pop();
}

void SessionServer::stopMatch() {
    if (!gameRunnimg)
        return;

    gameRunnimg = false;

    match->stop();
    server.stop();
}

bool SessionServer::isLobbyOpened() {
    return lobbyOpened;
}

bool SessionServer::isGameRunnimg() {
    return gameRunnimg;
}

nlohmann::json SessionServer::eventsToJSON(std::vector<std::shared_ptr<IEvent>> events) {
    nlohmann::json json;

    for (size_t i = 0; i < events.size(); i++) {
        size_t id = events[i]->getEventId();

        if (id == GAME_EVENT_MATCH_START || id == GAME_EVENT_MATCH_STOP) {
            json[i]["eventId"] = id;
            continue;
        }

        if (id == GAME_EVENT_ENTITY_IS_ALIVE_CHANGED ||
            id == GAME_EVENT_ENTITY_HP_CHANGED ||
            id == GAME_EVENT_ENTITY_POSITION_CHANGED) {
            IEventEntity* eventEntity = dynamic_cast<IEventEntity*>(events[i].get());
            json[i]["eventId"] = id;
            json[i]["entityId"] = eventEntity->getEntityId();
            json[i]["value"] = eventEntity->getValue();
            continue;
        }
    }

    return json;
}
