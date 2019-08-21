//
// Created by mfbut on 1/27/2018.
//

#ifndef HOARDINGCPPVERSION_PROPERTYMANAGER_H
#define HOARDINGCPPVERSION_PROPERTYMANAGER_H
#include <map>
#include <vector>

#include "Property.h"
#include "PropertySet.h"

namespace Monopoly {
  class Board;
  class Player;

  class PropertyManager {
   public:
    explicit PropertyManager(Board& board, Rules& rules);

    PropertyManager(const PropertyManager& orig) = default;
    void takeOwnershipOf(Property& property);
    void takeOwnershipOf(PropertySet& propertySet);
    bool ownsEntireSet(const int setId) const;
    void givePropertiesTo(PropertyManager& receiver);
    void updateOwner(Player& newOwner);
    int getValue() const;
    void upgradeProperties(Board &board, const Rules &rules, int playerCash);
    std::vector<Property*> getUpgradableProperties(Board& board, const Rules& rules, int playerCash);
    std::vector<Property*> getSellableProperties(Board& board);
    void sellUpgrades(Board& board);
    void forceSellUpgrades(Board& board);

   private:
    std::map<int, PropertySet> propertySets;
    Board* boardPtr;
    Rules* rulesPtr;
   public:
    Board *getBoardPtr() const;
  };
}

#endif //HOARDINGCPPVERSION_PROPERTYMANAGER_H
