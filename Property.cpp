//
// Created by mfbut on 1/20/2018.
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Property.h"
#include "Player.h"

Monopoly::Property::Property(CSVReader& boardFile, const int spaceNumber, const Rules& rules)
    : Space(boardFile, spaceNumber, rules), setId(), intraSetId(), cost(), house_cost(), hotel_cost(), rent(),
      rent_with_house(), rent_with_hotel(), numHouses(0), maxHouses(rules.getNum_houses_before_hotel()){

  setId = boardFile.get_next_field_as_int();
  intraSetId = boardFile.get_next_field_as_int();
  name = boardFile.get_next_field();
  cost = boardFile.get_next_field_as_int();
  house_cost = boardFile.get_next_field_as_int();
  hotel_cost = boardFile.get_next_field_as_int();
  rent = boardFile.get_next_field_as_int();
  rent_with_house = boardFile.get_next_field_as_int();
  rent_with_hotel = boardFile.get_next_field_as_int();
}

int Monopoly::Property::getSetId() const {
  return setId;
}

int Monopoly::Property::getIntraSetId() const {
  return intraSetId;
}

int Monopoly::Property::getCost() const {
  return cost;
}

int Monopoly::Property::getHouse_cost() const {
  return house_cost;
}

int Monopoly::Property::getHotel_cost() const {
  return hotel_cost;
}

int Monopoly::Property::getRent() const {
  return rent;
}

int Monopoly::Property::getRent_with_house() const {
  return rent_with_house;
}

int Monopoly::Property::getRent_with_hotel() const {
  return rent_with_hotel;
}

Monopoly::Player* Monopoly::Property::getOwner() const {
  return owner;
}

int Monopoly::Property::getLanding_multiplier() const {
  return landing_multiplier;
}

void Monopoly::Property::setLanding_multiplier(int landing_multiplier) {
  this->landing_multiplier = landing_multiplier;
}

void Monopoly::Property::displayAttributes() const {
  std::string ownerName;

  if(owner) {
    ownerName = owner->getName();
  } else {
    ownerName = "None ";
  }

  std::cout.width(length_of_longest_player_name);
  std::cout << ownerName << " | ";
  std::cout << getUpgradeString() << " | ";
}

std::string Monopoly::Property::getOwnerName() const {
  if (owner != nullptr) {
    return owner->getName();
  } else {
    return "None";
  }
}

void Monopoly::Property::setOwner(Monopoly::Player* owner) {
  Property::owner = owner;
}

int Monopoly::Property::calculateRent(const Rules& rules) const {
  if(numHouses == 0) {
    return rent * (owner->ownsAllPropertiesInSet(setId) ? rules.getProperty_set_multiplier() : 1);
  } else if (numHouses == maxHouses + 1) {
    return rent_with_hotel;
  } else {
    return static_cast<int>(rent_with_house * pow(2, numHouses - 1));
  }

}
int Monopoly::Property::getUpgradeCost(const Monopoly::Rules &rules) const {
  if(numHouses == rules.getNum_houses_before_hotel()) {
    return hotel_cost;
  } else {
    return house_cost;
  }
}
void Monopoly::Property::upgrade(const Monopoly::Rules &rules) {
  numHouses++;
  owner->giveCash(-1 * getUpgradeCost(rules));
}
int Monopoly::Property::getNumHouses() const {
  return numHouses;
}
int Monopoly::Property::getSellPrice(const Monopoly::Rules &rules) const {
  if(numHouses == rules.getNum_houses_before_hotel() + 1) {
    return hotel_cost / 2;
  } else {
    return house_cost / 2;
  }
}
void Monopoly::Property::downgrade(const Monopoly::Rules &rules) {
  numHouses--;
  owner->giveCash(getSellPrice(rules));
}
std::string Monopoly::Property::getUpgradeString() const {
  /*std::string upgradeString;

  if(numHouses == maxHouses + 1) {
    upgradeString.push_back('H');
  } else {
    for(int i = 0; i < numHouses; ++i) {
      upgradeString.push_back('h');
      if(i > 5) {
        int num = maxHouses;
        num+= 1;
        num-=1;
      }
    }
  }

  return upgradeString;*/

  const std::string upgrade("Upgrades");
  std::string upgradeString;
  for (int i = 0; i < getNumHousesOn(); ++i) {
    upgradeString.push_back('h');
  }
  for (int i = 0; i < getNumHotelsOn(); ++i) {
    upgradeString.push_back('H');
  }
  unsigned long upgradeLength = upgradeString.size();

  for (unsigned long i = 0; i < upgrade.size() - upgradeLength; ++i) {
    upgradeString.push_back(' ');
  }

  return upgradeString;
}
void Monopoly::Property::setNumHouses(int numHouses) {
  Property::numHouses = numHouses;
}
void Monopoly::Property::display() const {
  Space::display();
}
void Monopoly::Property::activate(Monopoly::Player &activatingPlayer) {
  if (owner == nullptr) {
    if (activatingPlayer.getCash() >= getCost()) { //can afford the property
      bool toBuy = activatingPlayer.getBuyDecision(*this);
      if (toBuy) {
        std::cout << activatingPlayer.getName() << " bought " << name << " for $" << cost
                  << std::endl;
        activatingPlayer.purchase(*this);
      } else {
        activatingPlayer.setStartedAuction(true);
      }
    } else { // not enough money to buy property
      std::cout << activatingPlayer.getName() << ", you don't have enough money to afford " << name << ". "
                << name << " costs $" << cost << " but you only have $" << activatingPlayer.getCash()
                << std::endl;

    }
  } else if (owner->getId() == activatingPlayer.getId()) {// player landed on their own property
    std::cout << activatingPlayer.getName() << ", you landed on " << name << "which you already own" << std::endl;
  } else { //landed on a space another player owes
    activatingPlayer.pay(*owner, *this, rules);
  }
}
int Monopoly::Property::getNumHousesOn() const {
  if(numHouses > maxHouses) {
    return 0;
  } else {
    return numHouses;
  }
}
int Monopoly::Property::getNumHotelsOn() const {
  if(numHouses > maxHouses) {
    return numHouses - maxHouses;
  } else {
    return 0;
  }
}



