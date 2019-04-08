//
// Created by fktrc on 08.04.19.
//

#ifndef GAME_MOVEMENTSEQUENCE_HPP
#define GAME_MOVEMENTSEQUENCE_HPP

#include "Sequence.hpp"
#include "Actor.hpp"

class MovementSequence : public Sequence {
public:
    MovementSequence(const size_t id, size_t nextUpdateTimeMs, Actor* actor, Graph* graph, Point dest);
    void Update() override;

private:
    Actor* actor;
    Graph* graph;
    Point dest;
    Path path;

    bool isPathCorrect();
};

#endif //GAME_MOVEMENTSEQUENCE_HPP
