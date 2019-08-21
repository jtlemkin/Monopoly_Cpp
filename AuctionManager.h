//
// Created by James Lemkin on 2/19/18.
//

#ifndef HOARDINGCPPVERSION_AUCTIONMANAGER_H
#define HOARDINGCPPVERSION_AUCTIONMANAGER_H
#include <string>
#include "Space.h"
#include <iostream>
#include "Player.h"
namespace Monopoly {
  class AuctionManager {
   private:
    int highestBid;
    std::string highestBidderName;
    Property& property;
    int playerTurn;
    int numPlayersLeft;
    std::vector<Monopoly::Player*> auctionPlayers;
    void doSomethingWithPlayerTurn() const;
   public:
    AuctionManager(Property& property, std::vector<Player>& players, int playerTurn);
    int getHighestBid() const;
    void setHighestBid(int highestBid);
    const std::string &getHighestBidderName() const;
    void setHighestBidderName(const std::string &highestBidderName);
    int getBid(const Player& player) const;
  };
}
#endif //HOARDINGCPPVERSION_AUCTIONMANAGER_H
