//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_PROPERTY_H
#define HOARDINGCPPVERSION_PROPERTY_H
#include <string>
#include "CSVReader.h"
#include "Rules.h"
#include "Space.h"

namespace Monopoly {
  class Player;

  class Property : public Space  {
   public:
    Property(CSVReader& boardFile, const int spaceNumber, const Rules& rules);
    void setOwner(Player* owner);

    int getSetId() const;
    int getIntraSetId() const;
    int getCost() const;
    int getHouse_cost() const;
    int getHotel_cost() const;
    int getRent() const;
    int getRent_with_house() const;
    int getRent_with_hotel() const;
    Player* getOwner() const;
    std::string getOwnerName() const;

    void setNumHouses(int numHouses);

    int calculateRent(const Rules& rules) const;
    int getUpgradeCost(const Rules& rules) const;
    void upgrade(const Rules& rules);
    int getNumHouses() const;
    int getSellPrice(const Rules& rules) const;
    void downgrade(const Rules& rules);
    std::string getUpgradeString() const;
    int getNumHousesOn() const;
    int getNumHotelsOn() const;

    int getLanding_multiplier() const;
    void setLanding_multiplier(int landing_multiplier);

    void display() const override;
    void activate(Player& activatingPlayer) override;
    void displayAttributes() const override;

   private:
    int setId;
    int intraSetId;
    int cost;
    int house_cost;
    int hotel_cost;
    int rent;
    int rent_with_house;
    int rent_with_hotel;
    Player* owner;
    int landing_multiplier;
    int numHouses;
    int maxHouses;
  };
}

#endif //HOARDINGCPPVERSION_PROPERTY_H
