//
// Created by James Lemkin on 3/1/18.
//

#ifndef HOARDINGCPPVERSION_JAIL_H
#define HOARDINGCPPVERSION_JAIL_H
#include "Space.h"
#include "Player.h"
#include <iostream>
namespace Monopoly {
  class Jail : public Space {
   public:
    Jail(CSVReader& boardFile, const int spaceNumber, const Rules& rules);

    void display() const override;
    void activate(Player& activatingPlayer) override;
    void displayAttributes() const override;

   protected:
    int turnsInJail;
   public:
    int getTurnsInJail() const;
   protected:
    int bailCost;
   public:
    int getBailCost() const;
  };
}
#endif //HOARDINGCPPVERSION_JAIL_H
