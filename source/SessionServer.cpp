//
// Created by fktrc on 22.05.19.
//

#include "SessionServer.hpp"

void SessionServer::setupMatch(std::string levelName, std::string gameModeName) {
    if (gameRunnimg)
        return;

    match = std::make_unique<Match>();

    size_t gameModeId = 1;

    if (gameModeName == "TDM") {
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
        while (gameRunnimg) {
            std::vector<std::shared_ptr<IEvent>> events = match->getGameEvents().wait_and_pop();
            if (events.empty()) {
                break;
            }

            std::string msg = eventsToJSON(events);
            std::cout << msg << std::endl;
            server.sendMessage(msg);
        }
    }).detach();

    std::thread([this]() {
        while (gameRunnimg) {
            std::string msg = server.getReseiveQueue().wait_and_pop();
            std::cout << msg << std::endl;
        }
    }).detach();
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

std::string SessionServer::eventsToJSON(std::vector<std::shared_ptr<IEvent>> events) {
    json j;

    for (size_t i = 0; i < events.size(); i++) {
        size_t id = events[i]->getEventId();

        if (id == GAME_EVENT_MATCH_START || id == GAME_EVENT_MATCH_STOP) {
            j[i]["eventId"] = id;
            continue;
        }

        if (id == GAME_EVENT_ENTITY_IS_ALIVE_CHANGED ||
            id == GAME_EVENT_ENTITY_HP_CHANGED ||
            id == GAME_EVENT_ENTITY_POSITION_CHANGED) {
            IEventEntity* eventEntity = dynamic_cast<IEventEntity*>(events[i].get());
            j[i]["eventId"] = id;
            j[i]["entityId"] = eventEntity->getEntityId();
            j[i]["value"] = eventEntity->getValue();
            continue;
        }
    }

    return j.dump();
}
