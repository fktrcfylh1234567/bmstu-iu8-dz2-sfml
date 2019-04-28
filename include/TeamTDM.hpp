//
// Created by fktrc on 28.04.19.
//

#ifndef GAME_TEAMTDM_HPP
#define GAME_TEAMTDM_HPP

#include <ITeam.hpp>

class TeamTDM : public ITeam {
public:
    TeamTDM(size_t teamId) : teamId(teamId) {}

    size_t getTeamId() const override {
        return teamId;
    }

    const std::vector<size_t>& getCharactersIds() const override {
        return charactersIds;
    }

    void addCharacter(size_t characterId) override {
        charactersIds.push_back(characterId);
    }

private:
    size_t teamId;
    std::vector<size_t> charactersIds;
};


#endif //GAME_TEAMTDM_HPP
