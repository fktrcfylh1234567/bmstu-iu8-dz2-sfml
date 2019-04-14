//
// Created by fktrc on 11.04.19.
//

#ifndef GAME_INSTANCE_HPP
#define GAME_INSTANCE_HPP

typedef std::pair <size_t, size_t> Point;

class Instance {
    virtual void update(size_t currentTime) = 0;

    virtual size_t addCharacter(CharacterStats& characterStats) = 0;
    virtual void removeCharacter(size_t characterId) = 0;

    virtual void addMoveSequence(size_t characterId, Point& point) = 0;
    virtual void addAttackSequence(size_t characterId, size_t targetId) = 0;

    virtual void addSkillSequence(size_t characterId, size_t skillId) = 0;
    virtual void addSkillSequence(size_t characterId, size_t skillId, size_t targetId) = 0;
    virtual void addSkillSequence(size_t characterId, size_t skillId, Point& point) = 0;
    virtual void removeAllActiveCharacterSequences(size_t characterId) = 0;
};

#endif //GAME_INSTANCE_HPP
