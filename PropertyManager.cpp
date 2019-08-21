//
// Created by mfbut on 1/27/2018.
//

#include <iostream>
#include "PropertyManager.h"
#include "Board.h"
#include "Player.h"

Monopoly::PropertyManager::PropertyManager(Monopoly::Board& board, Monopoly::Rules& rules) : boardPtr(&board),
                                                                                             rulesPtr(&rules) {
  for (const auto& property : board.getProperties()) {
    if (propertySets.count(property->getSetId()) == 0) {
      propertySets[property->getSetId()] = PropertySet(property->getSetId());
    } else {
      propertySets.at(property->getSetId()).incNumPropertiesInSet();
    }
  }
}

void Monopoly::PropertyManager::takeOwnershipOf(Monopoly::Property& property) {
  propertySets.at(property.getSetId()).addProperty(property);
}

/**
 * Move all of the properties within the property set into this
 * property manager. Leaves the given propertySet empty
 * @param propertySet
 */
void Monopoly::PropertyManager::takeOwnershipOf(Monopoly::PropertySet& propertySet) {
  for (const auto& property : propertySet.getProperties()) {
    takeOwnershipOf(*property);
  }
  propertySet.clear();
}

bool Monopoly::PropertyManager::ownsEntireSet(const int setId) const {
  return propertySets.at(setId).ownsAll();
}

void Monopoly::PropertyManager::givePropertiesTo(Monopoly::PropertyManager& receiver) {
  for (auto& propertySet : propertySets) {
    receiver.takeOwnershipOf(propertySet.second); // second is the actual property. first is the property set id
  }
}

void Monopoly::PropertyManager::updateOwner(Monopoly::Player& newOwner) {
  for (auto& propertySet : propertySets) {
    propertySet.second.updateOwner(newOwner);
  }
}

int Monopoly::PropertyManager::getValue() const {
  int value = 0;

  for (const auto& propertySet : propertySets) {
    value += propertySet.second.getValue();
  }
  return value;
}
void Monopoly::PropertyManager::upgradeProperties(Monopoly::Board &board, const Monopoly::Rules &rules, int playerCash) {
  auto upgradableProperties = getUpgradableProperties(board, rules, playerCash);

  if(!upgradableProperties.empty()) {
    std::cout << "Which property do you want to upgrade?" << std::endl;

    int i = 0;
    for(const auto& property: upgradableProperties) {
      std::cout << i << ". " << property->getName() << " [$" << property->getUpgradeCost(rules) << "]" << std::endl;
      i++;
    }

    std::cout << "Your choice:" << std::endl;

    int choice;
    std::cin >> choice;

    upgradableProperties[choice]->upgrade(rules);
  } else {
    std::cout << "You don't have any properties that you can upgrade" << std::endl;
  }
}

std::vector<Monopoly::Property *> Monopoly::PropertyManager::getUpgradableProperties(Monopoly::Board &board,
                                                                           const Monopoly::Rules &rules,
                                                                           int playerCash) {
  std::vector<Monopoly::Property*> upgradableProperties;

  for(auto it = propertySets.begin(); it != propertySets.end(); ++it) {
    if(ownsEntireSet(it->first)) {
      if(rules.Must_build_evenly()) {
        int lowestNumHousesInSet = it->second.getLowestNumHousesInSet();
        for(auto& property: it->second.getProperties()) {
          if(playerCash >= property->getUpgradeCost(rules) && property->getNumHouses() == lowestNumHousesInSet
              && property->getNumHouses() < rules.getNum_houses_before_hotel() + 1) {
            upgradableProperties.emplace_back(property);
          }
        }
      } else {
        for(auto& property: it->second.getProperties()) {
          if(playerCash >= property->getUpgradeCost(rules)
              && property->getNumHouses() < rules.getNum_houses_before_hotel() + 1) {
            upgradableProperties.emplace_back(property);
          }
        }
      }
    }
  }

  return upgradableProperties;
}
std::vector<Monopoly::Property *> Monopoly::PropertyManager::getSellableProperties(Monopoly::Board &board) {
  std::vector<Monopoly::Property*> sellableProperties;

  for(auto it = propertySets.begin(); it != propertySets.end(); ++it) {
    if(ownsEntireSet(it->first)) {
      if(rulesPtr->Must_build_evenly()) {
        int greatestNumHousesInSet = it->second.getHighestNumHousesInSet();
        for(auto& property: it->second.getProperties()) {
          if(property->getNumHouses() == greatestNumHousesInSet && property->getNumHouses() > 0) {
            sellableProperties.emplace_back(property);
          }
        }
      } else {
        for(auto& property: it->second.getProperties()) {
          if(property->getNumHouses() > 0) {
            sellableProperties.emplace_back(property);
          }
        }
      }
    }
  }

  return sellableProperties;
}
void Monopoly::PropertyManager::sellUpgrades(Monopoly::Board &board) {
  auto sellableProperties = getSellableProperties(board);

  if(!sellableProperties.empty()) {
    std::cout << "Which property do you want to downgrade?" << std::endl;

    int i = 0;
    for(const auto& property: sellableProperties) {
      std::cout << i << ". " << property->getName() << " [$" << property->getSellPrice(*rulesPtr) << "]" << std::endl;
      i++;
    }

    std::cout << "Your choice:" << std::endl;

    int choice;
    std::cin >> choice;

    sellableProperties[choice]->downgrade(*rulesPtr);
  } else {
    std::cout << "You don't have any upgrades that you can sell" << std::endl;
  }
}
Monopoly::Board *Monopoly::PropertyManager::getBoardPtr() const {
  return boardPtr;
}
void Monopoly::PropertyManager::forceSellUpgrades(Monopoly::Board &board) {
  auto sellableProperties = getSellableProperties(board);

  if(!sellableProperties.empty()) {
    std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;

    int i = 0;
    for(const auto& property: sellableProperties) {
      std::cout << i << ". " << property->getName() << " [$" << property->getSellPrice(*rulesPtr) << "]" << std::endl;
      i++;
    }

    std::cout << "Your choice:" << std::endl;

    int choice;
    std::cin >> choice;

    sellableProperties[choice]->downgrade(*rulesPtr);
  } else {
    std::cout << "This shouldn't be happening" << std::endl;
  }
}

