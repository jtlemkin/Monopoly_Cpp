//
// Created by James Lemkin on 3/1/18.
//

#include "GoToJail.h"

Monopoly::GoToJail::GoToJail(Monopoly::CSVReader &boardFile, const int spaceNumber, const Monopoly::Rules &rules)
    : Space(boardFile, spaceNumber, rules) {
  name = boardFile.get_next_field();
  indexOfSpaceToGoTo = boardFile.get_next_field_as_int();
  boardFile.skip_line();

  jailPtr = nullptr;
}
void Monopoly::GoToJail::display() const {
  Space::display();
}
void Monopoly::GoToJail::activate(Monopoly::Player &activatingPlayer) {
  std::cout << activatingPlayer.getName() << ", you were sent to " << jailPtr->getName() << " for "
      << jailPtr->getTurnsInJail() << " turns" << std::endl;
  activatingPlayer.moveTo(*jailPtr);
  activatingPlayer.setJailPtr(jailPtr);
}
void Monopoly::GoToJail::displayAttributes() const {
  const std::string temp = "None ";
  std::cout << temp << " | ";
  std::cout << "         | ";
}
int Monopoly::GoToJail::getIndexOfSpaceToGoTo() const {
  return indexOfSpaceToGoTo;
}
void Monopoly::GoToJail::setJailPtr(Monopoly::Jail *jailPtr) {
  GoToJail::jailPtr = jailPtr;
}
