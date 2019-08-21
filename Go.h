//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_GO_H
#define HOARDINGCPPVERSION_GO_H

#include <string>
#include "CSVReader.h"
#include "Space.h"
#include "Player.h"
#include <iomanip>
#include <iostream>
namespace Monopoly {
  class Go : public Space {
   public:
    Go(CSVReader& boardFile, const int spaceNumber, const Rules& rules);

    void display() const override;
    void activate(Player& activatingPlayer) override;
    void displayAttributes() const override;

    int getSalary() const;
    int getLanding_multiplier() const;
    void setLanding_multiplier(int landing_multiplier);
   private:
    int salary;
    int landing_multiplier;
  };
}

#endif //HOARDINGCPPVERSION_GO_H
