//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_PLAYER_H
#define HOARDINGCPPVERSION_PLAYER_H
#include <string>
#include <map>

#include "Property.h"
#include "Space.h"
#include "PropertyManager.h"
#include "Rules.h"
#include "Move.h"
#include "PayTheBank.h"

namespace Monopoly {
  class Jail;

  class Player {
   public:
    static unsigned long length_of_longest_player_name;
    Player(int id, const std::string& name, int cash, Monopoly::Space* spaceOn, const PropertyManager& propertyManager);
    Player(const Player& player) = default;
    Space& getSpaceOn();
    virtual ~Player();

    void setOn(Space& space, bool activateSpace = true);
    void moveTo(Space& space, bool activateSpace = true);

    const std::string& getName() const;
    int getCash() const;
    void setCash(int cash);
    void giveCash(const int amount);

    void purchase(Property& property, int cost = -1);

    bool getBuyDecision(const Property& property) const;

    void pay(Monopoly::Player& owner, const Property& propertyOn, const Rules& rules);
    void pay(PayTheBank& bank, const Rules& rules);
    bool ownsAllPropertiesInSet(const int setId) const;
    int getNetWorth() const;
    void refreshReferencesTo();
    void upgradeProperties(Board& board, const Rules& rules);
    void sellUpgrades(Board& board);
    void removeAllUpgrades(Board& board, Rules& rules);

    Move getMove();

    void display();
    int getId() const;

    void goBankruptTo(Player& owner, const Property& propertyOn, int amount);
    void goBankruptTo(PayTheBank& bank, int amount);
    bool hasSellableProperties(Board& board);

    bool hasJailSentence();
    void getBailDecision();
    void bailOut();
    void serveTime();
    void endPrisonSentence();

   private:
    int id;
    std::string name;
    int cash;
    Move current_move;
    Space* spaceOn;
    PropertyManager propertyManager;
    bool startedAuction;
    Jail* jailPtr;
   public:
    void setJailPtr(Jail *jailPtr);
   private:
    int turnsLeftInJail;
   public:
    int getTurnsLeftInJail() const;
   public:
    void setStartedAuction(bool startedAuction);
   public:
    bool isStartedAuction() const;
  };
}

#endif //HOARDINGCPPVERSION_PLAYER_H
