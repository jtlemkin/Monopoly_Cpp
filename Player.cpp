//
// Created by mfbut on 1/20/2018.
//

#include "Player.h"
#include "FreeParking.h"
#include "Jail.h"

unsigned long Monopoly::Player::length_of_longest_player_name;

Monopoly::Player::Player(int id,
                         const std::string& name,
                         int cash,
                         Space* spaceOn,
                         const PropertyManager& propertyManager)
    : id(id), name(name), cash(cash), spaceOn(spaceOn), propertyManager(propertyManager), startedAuction(false),
      jailPtr(nullptr), turnsLeftInJail(0) {

}

const std::string& Monopoly::Player::getName() const {
  return name;
}

int Monopoly::Player::getCash() const {
  return cash;
}

void Monopoly::Player::setCash(int cash) {
  Player::cash = cash;
}

void Monopoly::Player::giveCash(const int amount) {
  cash += amount;
}

Monopoly::Move Monopoly::Player::getMove() {
  int move_number;

  if(hasJailSentence()) {
    if(getTurnsLeftInJail() == 0) {
      endPrisonSentence();

      if(cash < 0) {
        return Move(4);
      }
    } else {
      getBailDecision();
    }
  }

  std::cout << name << " please enter your move" << std::endl;
  std::cout << "1 to roll dice" << std::endl;
  std::cout << "2 to upgrade a property with a house or hotel" <<std::endl;
  std::cout << "3 to sell a house or hotel" << std::endl;
  std::cout << "4 to leave the game" << std::endl;
  std::cout << "Your move: ";
  std::cin >> move_number;
  current_move = Move(move_number);

  return current_move;
}

void Monopoly::Player::display() {
  std::cout << '[' << name << " : $" << cash << ']';
}

int Monopoly::Player::getId() const {
  return id;
}

Monopoly::Space& Monopoly::Player::getSpaceOn() {
  return *spaceOn;
}

void Monopoly::Player::setOn(Space& space, bool activateSpace) {
  this->spaceOn = &space;
  space.addPlayer(*this);

  if (activateSpace) {
    space.activate(*this);
  }
}

void Monopoly::Player::moveTo(Monopoly::Space& space, bool activateSpace) {
  spaceOn->removePlayer(*this);
  setOn(space);

}

bool Monopoly::Player::getBuyDecision(const Monopoly::Property& property) const {
  char choice;
  std::cout << "Would you like to buy " << property.getName() << " for $" << property.getCost() << '?' << std::endl;
  std::cout << "Rent on " <<property.getName() << " is $" << property.getRent() << std::endl;
  std::cout << "Enter y for yes or n for no: ";
  std::cin >> choice;
  choice = static_cast<char>(tolower(choice));
  if (!(choice == 'y' || choice == 'n')) {
    std::cout << "Unknown choice of " << choice << " received for buy decision" << std::endl;
    return false;
  }
  return choice == 'y';
}

void Monopoly::Player::purchase(Monopoly::Property& property, int cost) {
  if(cost == -1) {
    cash -= property.getCost();
  } else {
    cash -= cost;
  }
  property.setOwner(this);
  propertyManager.takeOwnershipOf(property);
}

void Monopoly::Player::pay(Monopoly::Player& owner, const Property& propertyOn, const Rules& rules) {
  int amount = propertyOn.calculateRent(rules);
  if (cash >= amount) {
    cash -= amount;
    owner.cash += amount;

    std::cout << name << " paid " << owner.name << " $" << amount << " for landing on " << propertyOn.getName()
              << std::endl;
  } else if (hasSellableProperties(*propertyManager.getBoardPtr())) {
    std::cout << "You have $" << cash << " but you owe $" << amount << std::endl;

    propertyManager.forceSellUpgrades(*propertyManager.getBoardPtr());
    pay(owner, propertyOn, rules);
  } else {
    goBankruptTo(owner, propertyOn, amount);
  }
}

bool Monopoly::Player::ownsAllPropertiesInSet(const int setId) const {
  return propertyManager.ownsEntireSet(setId);
}

/*
 * Update all the references to this player so that they actually point to this player
 */
void Monopoly::Player::refreshReferencesTo() {
  propertyManager.updateOwner(*this);
  spaceOn->addPlayer(*this);
}

Monopoly::Player::~Player() {
  //spaceOn->removePlayer(*this);
}

int Monopoly::Player::getNetWorth() const {

  return cash + propertyManager.getValue();
}
void Monopoly::Player::upgradeProperties(Monopoly::Board &board, const Monopoly::Rules &rules) {
  propertyManager.upgradeProperties(board, rules, cash);
}
bool Monopoly::Player::isStartedAuction() const {
  return startedAuction;
}
void Monopoly::Player::setStartedAuction(bool startedAuction) {
  Player::startedAuction = startedAuction;
}
void Monopoly::Player::sellUpgrades(Monopoly::Board &board) {
  propertyManager.sellUpgrades(board);
}
void Monopoly::Player::removeAllUpgrades(Monopoly::Board &board, Monopoly::Rules &rules) {
  auto properties = propertyManager.getSellableProperties(board);

  for(auto& property: properties) {
    property->setNumHouses(0);
  }
}
void Monopoly::Player::goBankruptTo(Monopoly::Player &owner, const Monopoly::Property &propertyOn, int amount) {
  owner.cash += cash;
  cash -= amount;
  propertyManager.givePropertiesTo(owner.propertyManager); // give all of our properties to the player we owe
  owner.propertyManager.updateOwner(owner); // the player we are paying to now owns all those properties
  std::cout << name << " went bankrupt to " << owner.name << " for landing on " << propertyOn.getName() << std::endl;
}
bool Monopoly::Player::hasSellableProperties(Monopoly::Board &board) {
  return !propertyManager.getSellableProperties(board).empty();
}
void Monopoly::Player::pay(Monopoly::PayTheBank &bank, const Rules& rules) {
  int amount = bank.getAmountToBePaid();
  if (cash >= amount) {
    cash -= amount;

    std::cout << name << " paid the bank $" << amount << " for landing on " << bank.getName() << std::endl;
  } else if (hasSellableProperties(*propertyManager.getBoardPtr())) {
    std::cout << "You have $" << cash << " but you owe $" << amount << std::endl;

    propertyManager.forceSellUpgrades(*propertyManager.getBoardPtr());
  } else {
    goBankruptTo(bank, amount);
  }
}
void Monopoly::Player::goBankruptTo(Monopoly::PayTheBank &bank, int amount) {
  cash -= amount;
  //maybe add code getting rid of property ownership
  std::cout << name << " went bankrupt by landing on " << bank.getName() << std::endl;
}

bool Monopoly::Player::hasJailSentence() {
  return jailPtr != nullptr;
}
void Monopoly::Player::getBailDecision() {
  std::cout << name << " you are in jail for " << turnsLeftInJail << " turns." << std::endl;

  if(cash >= jailPtr->getBailCost()) {
    std::cout << "Would you like to pay $" << jailPtr->getBailCost() << " to leave jail early?" << std::endl;
    std::cout << "y for yes and n for no:" << std::endl;

    char choice;
    std::cin >> choice;

    choice = static_cast<char>(tolower(choice));
    if(choice == 'y') {
      bailOut();
    }
  }
}
void Monopoly::Player::bailOut() {
  int bail = jailPtr->getBailCost();
  if (cash >= bail) {
    cash -= bail;
  } else if (hasSellableProperties(*propertyManager.getBoardPtr())) {
    std::cout << "You have $" << cash << " but you owe $" << bail << std::endl;

    propertyManager.forceSellUpgrades(*propertyManager.getBoardPtr());
  } else {
    cash -= bail;
    std::cout << name << " went bankrupt when paying to leave jail" << std::endl;
  }

  jailPtr = nullptr;

  if (FreeParking::putMoneyInFreeParking) {
    FreeParking::addToCashPayout(bail);
  }
}
void Monopoly::Player::setJailPtr(Monopoly::Jail *jailPtr) {
  Player::jailPtr = jailPtr;
  this->turnsLeftInJail = jailPtr->getTurnsInJail();
}
void Monopoly::Player::serveTime() {
  std::cout << "You are still stuck in jail" << std::endl;
  turnsLeftInJail--;
}
int Monopoly::Player::getTurnsLeftInJail() const {
  return turnsLeftInJail;
}
void Monopoly::Player::endPrisonSentence() {
  if(cash >= jailPtr->getBailCost()) {
    std::cout << name << ", you had to pay $" << jailPtr->getBailCost() << " to get out of jail" << std::endl;
  }

  bailOut();
}
