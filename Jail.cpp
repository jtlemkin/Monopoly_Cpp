//
// Created by James Lemkin on 3/1/18.
//

#include "Jail.h"
Monopoly::Jail::Jail(Monopoly::CSVReader &boardFile, const int spaceNumber, const Monopoly::Rules &rules)
    : Space(boardFile, spaceNumber, rules) {
  name = boardFile.get_next_field();
  turnsInJail = boardFile.get_next_field_as_int();
  bailCost = boardFile.get_next_field_as_int();
  boardFile.skip_line();
}
void Monopoly::Jail::display() const {
  Space::display();
}
void Monopoly::Jail::activate(Monopoly::Player &activatingPlayer) {

}
void Monopoly::Jail::displayAttributes() const {
  const std::string temp = "None ";
  std::cout << temp << " | ";
  std::cout << "         | ";
}
int Monopoly::Jail::getTurnsInJail() const {
  return turnsInJail;
}
int Monopoly::Jail::getBailCost() const {
  return bailCost;
}
