//
// Created by fktrc on 22.05.19.
//

#include "SessionServer.hpp"

void SessionServer::setupMatch(std::string levelName, std::string gameModeName) {
    match = std::make_unique<Match>();

    size_t gameModeId = 1;

    if (gameModeName == "tdm") {
        gameModeId = 1;
    }

    match->setupGame(levelName, gameModeId);
}

void SessionServer::createLobby() {
    lobbyOpened = true;
    server.start();
}

void SessionServer::startMatch() {
    lobbyOpened = false;
    gameRunnimg = true;

    match->run();
    server.closeLobby();

    std::thread([this]() {
        while (true) {
            std::shared_ptr<IEvent> event = match->getGameEvents().wait_and_pop();
            if (event == nullptr) {
                break;
            }

            std::string msg = eventToJSON(event);
            server.sendMessage(msg);
        }
    }).detach();

    match->getGameEvents().wait_and_pop();
}

void SessionServer::stopMatch() {
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

nlohmann::json SessionServer::eventToJSON(std::shared_ptr<IEvent> event) {
    size_t id = event->getEventId();

    if (id == GAME_EVENT_MATCH_START || id == GAME_EVENT_MATCH_STOP) {
        nlohmann::json json;
        json["eventId"] = id;
        return json;
    }

    if (id == GAME_EVENT_ENTITY_IS_ALIVE_CHANGED ||
        id == GAME_EVENT_ENTITY_HP_CHANGED ||
        id == GAME_EVENT_ENTITY_POSITION_CHANGED) {
        IEventEntity* eventEntity = dynamic_cast<IEventEntity*>(event.get());

        nlohmann::json json;
        json["eventId"] = id;
        json["entityId"] = eventEntity->getEntityId();
        json["value"] = eventEntity->getValue();
        return json;
    }

    return nlohmann::json();
}
