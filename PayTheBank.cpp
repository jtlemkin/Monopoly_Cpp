//
// Created by James Lemkin on 3/1/18.
//

#include "PayTheBank.h"
#include "Player.h"
#include "FreeParking.h"

Monopoly::PayTheBank::PayTheBank(Monopoly::CSVReader &boardFile, const int spaceNumber, const Monopoly::Rules &rules)
    : Space(boardFile, spaceNumber, rules) {
  name = boardFile.get_next_field();
  amountToBePaid = boardFile.get_next_field_as_int();
  boardFile.skip_line();
}
void Monopoly::PayTheBank::display() const {
  Space::display();
}
void Monopoly::PayTheBank::activate(Monopoly::Player &activatingPlayer) {
  activatingPlayer.pay(*this, rules);

  if(rules.isPut_money_in_free_parking()) {
    FreeParking::addToCashPayout(amountToBePaid);
  }
}
void Monopoly::PayTheBank::displayAttributes() const {
  const std::string temp = "None ";
  std::cout << temp << " | ";
  std::cout << "         | ";
}
int Monopoly::PayTheBank::getAmountToBePaid() const {
  return amountToBePaid;
}
