//
// Created by James Lemkin on 2/19/18.
//

#include "AuctionManager.h"
Monopoly::AuctionManager::AuctionManager(Property& property, std::vector<Monopoly::Player>& players, int playerTurn)
    : highestBid(0), highestBidderName(), property(property), playerTurn(playerTurn),
      numPlayersLeft(static_cast<int>(players.size())), auctionPlayers() {
  int currentBid = 0;
  std::cout << "Starting the auction for " << property.getName() << std::endl;

  for(auto& player: players) {
    auctionPlayers.push_back(&player);
  }

  auto it = auctionPlayers.begin() + playerTurn;
  while(!((numPlayersLeft == 1 && highestBid != 0) || numPlayersLeft == 0)) {
    if(it == auctionPlayers.end()) {
      it = auctionPlayers.begin();
    }

    currentBid = getBid(**it);

    if(currentBid > highestBid) {
      highestBid = currentBid;
      highestBidderName = (*it)->getName();
      it++;
    } else {
      auctionPlayers.erase(it);
      numPlayersLeft--;
    }
  }

  if(highestBid == 0) {
    std::cout << "No one decided to purchase " << property.getName() << std::endl;
  } else {
    std::cout << auctionPlayers.front()->getName() << " won " << property.getName() << " for $"
              << highestBid << std::endl;
    auctionPlayers.front()->purchase(property, highestBid);
  }
}

int Monopoly::AuctionManager::getHighestBid() const {
  return highestBid;
}
void Monopoly::AuctionManager::setHighestBid(int highestBid) {
  AuctionManager::highestBid = highestBid;
}
const std::string &Monopoly::AuctionManager::getHighestBidderName() const {
  return highestBidderName;
}
void Monopoly::AuctionManager::setHighestBidderName(const std::string &highestBidderName) {
  AuctionManager::highestBidderName = highestBidderName;
}
int Monopoly::AuctionManager::getBid(const Player& player) const {
  int bid;

  if(highestBid == 0) {
    std::cout << "No one has bid on " << property.getName() << " [$ " << property.getCost() << "] yet" << std::endl;
  } else {
    std::cout << "The current bid for " << property.getName() << " [$ " << property.getCost() << "] is $" << highestBid
              << " by " << highestBidderName << std::endl;
  }

  std::cout << player.getName() << ", enter a bid of at least $" << highestBid + 1
            << " to bid on the property or a value less than that to leave the auction" << std::endl;
  std::cout << "Your bid: " << std::endl;

  std::cin >> bid;

  return bid;
}
void Monopoly::AuctionManager::doSomethingWithPlayerTurn() const {
  int butts = playerTurn;

  butts += 1;
}
