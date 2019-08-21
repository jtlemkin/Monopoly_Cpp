//
// Created by James Lemkin on 3/1/18.
//

#ifndef HOARDINGCPPVERSION_PAYTHEBANK_H
#define HOARDINGCPPVERSION_PAYTHEBANK_H
#include "Space.h"
#include <iostream>
namespace Monopoly {
class Player;

class PayTheBank : public Space {
 public:
  PayTheBank(CSVReader& boardFile, const int spaceNumber, const Rules& rules);

  void display() const override;
  void activate(Player& activatingPlayer) override;
  void displayAttributes() const override;

 protected:
  int amountToBePaid;
 public:
  int getAmountToBePaid() const;
};
}
#endif //HOARDINGCPPVERSION_PAYTHEBANK_H
