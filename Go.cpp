//
// Created by mfbut on 1/20/2018.
//

#include "Go.h"

Monopoly::Go::Go(CSVReader& boardFile, const int spaceNumber, const Rules& rules)
    : Space(boardFile, spaceNumber, rules), landing_multiplier(1) {
  salary = boardFile.get_next_field_as_int();
  name = boardFile.get_next_field();
  boardFile.skip_line();
}

int Monopoly::Go::getSalary() const {
  return salary;
}

int Monopoly::Go::getLanding_multiplier() const {
  return landing_multiplier;
}

void Monopoly::Go::setLanding_multiplier(int landing_multiplier) {
  this->landing_multiplier = landing_multiplier;
}

void Monopoly::Go::displayAttributes() const {
  const std::string temp = "None ";
  std::cout << temp << " | ";
  std::cout << "         | ";
}
void Monopoly::Go::activate(Monopoly::Player &activatingPlayer) {
  activatingPlayer.giveCash(getSalary() * (rules.getSalary_multiplier_for_landing_on_go() - 1));
}
void Monopoly::Go::display() const {
  Space::display();
}
