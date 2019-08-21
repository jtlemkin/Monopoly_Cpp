//
// Created by mfbut on 1/27/2018.
//

#ifndef HOARDINGCPPVERSION_PROPERTYSET_H
#define HOARDINGCPPVERSION_PROPERTYSET_H
#include <vector>
#include <map>
#include "Property.h"

namespace Monopoly {
  class Player;
  class PropertySet {
   public:
    explicit PropertySet(int setId = -99);
    //explicit PropertySet(const Property& property);
    PropertySet(const PropertySet& orig) = default;
    void incNumPropertiesInSet();
    void addProperty(Property& property);
    void removeProperty(const Property& property);
    void clear();
    bool ownsAll() const;
    const std::vector<Property*>& getProperties() const;
    void updateOwner(Player& newOwner);
    void deleteSelf();
    int getValue() const;
    virtual ~PropertySet();
    int getLowestNumHousesInSet() const;
    int getHighestNumHousesInSet() const;
   private:
    int setId;
    int numPropertiesInSet;

    std::vector<Property*> properties;
  };

}

#endif //HOARDINGCPPVERSION_PROPERTYSET_H
