//
// Created by James Lemkin on 3/1/18.
//

#ifndef HOARDINGCPPVERSION_FREEPARKING_H
#define HOARDINGCPPVERSION_FREEPARKING_H
#include "Space.h"
#include "Player.h"
#include <iostream>
namespace Monopoly {
  class FreeParking : public Space {
   public:
    FreeParking(CSVReader& boardFile, const int spaceNumber, const Rules& rules);

    void display() const override;
    void activate(Player& activatingPlayer) override;
    void displayAttributes() const override;

    static void addToCashPayout(int amount);
    static bool putMoneyInFreeParking;

   private:
    static int cashPayout;
  };
}
#endif //HOARDINGCPPVERSION_FREEPARKING_H
