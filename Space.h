//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_SPACE_H
#define HOARDINGCPPVERSION_SPACE_H

#include <memory>
#include <vector>

#include "CSVReader.h"
#include "Rules.h"

namespace Monopoly {
  class Player;
  //class Go;

  enum class SpaceType { goSpace, propertySpace, freeParking, payTheBank, jail, goToJail, errorSpace };

  class Space {
   public:
    Space(CSVReader& boardFile, const int spaceNumber, const Rules& rules);

    virtual void display() const;
    virtual void activate(Player& activatingPlayer) = 0;
    virtual void displayAttributes() const = 0;

    int getSpaceNumber() const;
    const std::string& getName() const;
    SpaceType getSpaceType() const;

    void addPlayer(Player& player);
    void removePlayer(const Player& player);
    void removeAllPlayers();

    static unsigned long length_of_longest_space_name;
    static unsigned long length_of_longest_player_name;

    static SpaceType get_space_type(std::string space_type_string);
    /*static std::unique_ptr<Space> factory(CSVReader& boardFile, const int spaceNumber, const Rules& rules,
                                          Monopoly::SpaceType type);*/

   protected:
    SpaceType spaceType;
    std::vector<Player*> playersOnSpace;
    int spaceNumber;
    const Rules& rules;
    std::string name;
  };
}

#endif //HOARDINGCPPVERSION_SPACE_H
