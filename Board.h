//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_BOARD_H
#define HOARDINGCPPVERSION_BOARD_H
#include <vector>
#include <string>
#include "Space.h"
#include "Rules.h"
#include "Go.h"
#include "Property.h"
#include "MonopolyUtility.h"
#include "FreeParking.h"
#include "GoToJail.h"

namespace Monopoly {
  class Space;
  class Board {
   public:
    Board(const std::string& boardFileName, const Rules& rules);
    void display() const;
    Space* getSpacePtr(int spaceNum);
    Go* getGoSpace();
    int getNumSpaces() const;
    const std::vector<std::unique_ptr<Space> >& getSpaces() const;
    std::vector<Property*> getProperties();
    void removeAllPlayers();
    int getNumSets() const;
    int getGoSalary() const;
    void linkGoToJailsWithJails();
    std::vector<GoToJail*> getGoToJails();
   private:
    std::vector<std::unique_ptr<Space> > spacePtrs;
    unsigned long calc_length_of_longest_space_name() const;
    int numSets;
    int goSalary;
    int calculateNumSet();
  };
}

#endif //HOARDINGCPPVERSION_BOARD_H
