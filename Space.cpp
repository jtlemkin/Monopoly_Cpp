//
// Created by mfbut on 1/20/2018.
//
#include <iostream>
#include <iomanip>
#include "Space.h"
#include "MonopolyUtility.h"
#include "Player.h"

unsigned long Monopoly::Space::length_of_longest_space_name;
unsigned long Monopoly::Space::length_of_longest_player_name;

Monopoly::Space::Space(CSVReader& boardFile, const int spaceNumber, const Rules& rules)
    : spaceNumber(spaceNumber), rules(rules), name() {
}

void Monopoly::Space::display() const {
  const auto frmt_flags = std::cout.flags();

  std::cout.width(length_of_longest_space_name);
  std::cout << name << " | ";

  displayAttributes();

  std::cout.flags(frmt_flags);

  auto player = playersOnSpace.cbegin();
  for (; player != playersOnSpace.cend(); ++player) {
    if (player + 1 == playersOnSpace.cend()) {
      break;
    }

    (*player)->display();
    std::cout << ", ";

  }

  if (player != playersOnSpace.cend()) {
    (*player)->display();
  }

}

const std::string& Monopoly::Space::getName() const {
  return name;
}

void Monopoly::Space::addPlayer(Monopoly::Player& player) {
  auto playerIt = playersOnSpace.cbegin();
  for (; playerIt != playersOnSpace.cend(); ++playerIt) {
    if (player.getId() < (*playerIt)->getId()) {
      break;
    }
  }
  playersOnSpace.insert(playerIt, &player);
}

void Monopoly::Space::removePlayer(const Monopoly::Player& player) {
  for (auto playerIt = playersOnSpace.cbegin(); playerIt != playersOnSpace.cend(); ++playerIt) {
    if ((*playerIt)->getId() == player.getId()) {
      playersOnSpace.erase(playerIt);
      return;
    }
  }
}

void Monopoly::Space::removeAllPlayers() {
  playersOnSpace.clear();
}

Monopoly::SpaceType Monopoly::Space::getSpaceType() const {
  return spaceType;
}

int Monopoly::Space::getSpaceNumber() const {
  return spaceNumber;
}

void Monopoly::Space::activate(Monopoly::Player& activatingPlayer) {
  /*if (spaceType == SpaceType::goSpace) {
    // -1 below because they've already been given some of the salary for
    // "passing" go
    activatingPlayer.giveCash(goPtr->getSalary() * (rules.getSalary_multiplier_for_landing_on_go() - 1));
  } else if (spaceType == SpaceType::propertySpace) {
    Player* owner = propertyPtr->getOwner();
    if (owner == nullptr) {
      if (activatingPlayer.getCash() >= propertyPtr->getCost()) { //can afford the property
        bool toBuy = activatingPlayer.getBuyDecision(*this);
        if (toBuy) {
          std::cout << activatingPlayer.getName() << " bought " << getName() << " for $" << propertyPtr->getCost()
                    << std::endl;
          activatingPlayer.purchase(*propertyPtr);
        } else {
          activatingPlayer.setStartedAuction(true);
        }
      } else { // not enough money to buy property
        std::cout << activatingPlayer.getName() << ", you don't have enough money to afford " << getName() << ". "
                  << getName() << " costs $" << getCost() << " but you only have $" << activatingPlayer.getCash()
                  << std::endl;

      }
    } else if (owner->getId() == activatingPlayer.getId()) {// player landed on their own property
      std::cout << activatingPlayer.getName() << ", you landed on " << getName() << "which you already own" << std::endl;
    } else { //landed on a space another player owes
      activatingPlayer.pay(*owner, *propertyPtr, rules);
    }
  }*/
}

/*int Monopoly::Space::getCost() const {
  if (spaceType == SpaceType::propertySpace) {
    return propertyPtr->getCost();
  } else {
    std::cout << "Get Cost called on non Property Space" << std::endl;
    return -99;
  }
}*/

/*int Monopoly::Space::getSetId() const {
  if (spaceType == SpaceType::propertySpace) {
    return propertyPtr->getSetId();
  } else {
    return -99;
  }
}*/

/*int Monopoly::Space::getIntraSetId() const {
  if (spaceType == SpaceType::propertySpace) {
    return propertyPtr->getIntraSetId();
  } else {
    return -99;
  }
}*/

/*int Monopoly::Space::getBasicRent() const {
  if (spaceType == SpaceType::propertySpace) {
    return propertyPtr->getRent();
  } else {
    return -99;
  }
}*/
/*std::unique_ptr<Monopoly::Property> &Monopoly::Space::getPropertyPtr() {
  return propertyPtr;
}*/
/*std::unique_ptr<Monopoly::Space> Monopoly::Space::factory(CSVReader& boardFile, const int spaceNumber,
                                                          const Rules& rules, Monopoly::SpaceType type) {
  if(type == SpaceType::goSpace) {
    return std::make_unique<Go>(boardFile, spaceNumber, rules);
  }

  return nullptr;
}*/
Monopoly::SpaceType Monopoly::Space::get_space_type(std::string space_type_string) {
  SpaceType spaceType;
  if (space_type_string == "Go") {
    spaceType = SpaceType::goSpace;
  } else if (space_type_string == "Property") {
    spaceType = SpaceType::propertySpace;
  } else if (space_type_string == "FreeParking") {
    spaceType = SpaceType::freeParking;
  } else if (space_type_string == "Pay") {
    spaceType = SpaceType::payTheBank;
  } else if (space_type_string == "Jail") {
    spaceType = SpaceType::jail;
  } else if (space_type_string == "GoToJail") {
    spaceType = SpaceType::goToJail;
  } else {
    std::cout << "Unrecognized Space type found" << std::endl;
    spaceType = SpaceType::errorSpace;
  }

  return spaceType;
}







