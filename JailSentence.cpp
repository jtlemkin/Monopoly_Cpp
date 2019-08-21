//
// Created by James Lemkin on 3/3/18.
//

#include "JailSentence.h"
#include "Player.h"
Monopoly::JailSentence::JailSentence(int prisonTermLength, int bail, Monopoly::Player *convict) {
  turnsLeftInJail = prisonTermLength;
  this->bail = bail;
  this->convict = convict;
}

void Monopoly::JailSentence::getBailDecision() {
  std::cout << convict->getName() << " you are in jail for " << turnsLeftInJail << " turns." << std::endl;
  std::cout << "Would you like to pay $" << bail << " to leave jail early?" << std::endl;
  std::cout << "y for yes and n for no:" << std::endl;

  char choice;
  std::cin >> choice;

  choice = static_cast<char>(tolower(choice));
  if(choice == 'y') {
    bailOut();
  }
}
void Monopoly::JailSentence::bailOut() {
  convict->giveCash(-bail);
}
