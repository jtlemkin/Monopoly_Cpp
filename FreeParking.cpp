//
// Created by James Lemkin on 3/1/18.
//

#include "FreeParking.h"

int Monopoly::FreeParking::cashPayout = 0;
bool Monopoly::FreeParking::putMoneyInFreeParking = false;

Monopoly::FreeParking::FreeParking(Monopoly::CSVReader &boardFile, const int spaceNumber, const Monopoly::Rules &rules)
    : Space(boardFile, spaceNumber, rules) {
  name = boardFile.get_next_field();
  boardFile.skip_line();

  FreeParking::putMoneyInFreeParking = rules.isPut_money_in_free_parking();
}
void Monopoly::FreeParking::display() const {
  Space::display();
}
void Monopoly::FreeParking::activate(Monopoly::Player &activatingPlayer) {
  activatingPlayer.giveCash(cashPayout);

  if(cashPayout != 0) {
    std::cout << activatingPlayer.getName() << " got $" << cashPayout << " for landing on " << name << std::endl;
  }

  cashPayout = 0;
}

void Monopoly::FreeParking::displayAttributes() const {
  const std::string temp = "None ";
  std::cout << temp << " | ";
  std::cout << "         | ";
}

void Monopoly::FreeParking::addToCashPayout(int amount) {
  FreeParking::cashPayout += amount;
}
