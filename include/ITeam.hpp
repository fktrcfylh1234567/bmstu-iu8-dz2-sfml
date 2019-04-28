//
// Created by fktrc on 28.04.19.
//

#ifndef GAME_ITEAM_HPP
#define GAME_ITEAM_HPP


class ITeam {
public:
    virtual size_t getTeamId() const = 0;
    virtual const std::vector<size_t>& getCharactersIds() const = 0;
    virtual void addCharacter(size_t characterId) = 0;
};


#endif //GAME_ITEAM_HPP
