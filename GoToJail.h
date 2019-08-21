//
// Created by James Lemkin on 3/1/18.
//

#ifndef HOARDINGCPPVERSION_GOTOJAIL_H
#define HOARDINGCPPVERSION_GOTOJAIL_H
#include "Space.h"
#include "Player.h"
#include "Jail.h"
#include <iostream>
namespace Monopoly {
  class GoToJail : public Space {
   public:
    GoToJail(CSVReader &boardFile, const int spaceNumber, const Rules &rules);

    void display() const override;
    void activate(Player &activatingPlayer) override;
    void displayAttributes() const override;

    int getIndexOfSpaceToGoTo() const;

   protected:
    int indexOfSpaceToGoTo;
    Jail* jailPtr;
   public:
    void setJailPtr(Jail *jailPtr);
  };
}


#endif //HOARDINGCPPVERSION_GOTOJAIL_H
