//
// Created by mfbut on 1/20/2018.
//

#include "GameState.h"
#include "MonopolyUtility.h"
#include <iostream>
#include "Move.h"
#include "PropertyManager.h"

Monopoly::GameState::GameState(const std::string& RulesFileName,
                               const std::string& BoardFileName,
                               const std::string& RandomFileName,
                               const std::vector<std::string>& playerNames)
    : rules(RulesFileName),
      board(BoardFileName, rules),
      diceRoller(RandomFileName),
      turn_count(0),
      player_turn(0),
      players() {

  PropertyManager emptyPropertyManager(board, rules);

  for (unsigned int i = 0; i < playerNames.size(); ++i) {
    players.emplace_back(i, playerNames[i], rules.getStarting_cash(), board.getSpacePtr(0), emptyPropertyManager);
  }

  /*
   * Placing the player on the space needed to be done after
   * all the players were created because the players'  locations
   * in memory keep moving as they get inserted into the players
   * vector
   */
  for (auto& player : players) {
    player.setOn(*board.getGoSpace(), false);
  }

  Space::length_of_longest_player_name =
      Utility::max(Utility::get_max_string_length(playerNames), std::string("Owner").size());

}

void Monopoly::GameState::display() const {
  board.display();
}

std::vector<std::string> Monopoly::GameState::get_player_names() {
  int num_players;
  std::vector<std::string> names;

  std::cout << "Enter how many players will be playing: ";
  std::cin >> num_players;
  names.resize(num_players);

  for (int i = 0; i < num_players; ++i) {
    std::cout << "Enter the name of player " << i + 1<< ": ";
    std::cin >> names[i];
  }
  return names;
}

void Monopoly::GameState::playGame() {
  Move move;
  while (!isGameOver()){
    do {
      display();
      move = getCurrentPlayer().getMove();
      make_move(getCurrentPlayer(), move);
    } while (!move.endsTurn);
    changeTurn();
  }
  display();
  declareWinner();
}

/**
 * Check if the game is over or not
 * @return
 */
bool Monopoly::GameState::isGameOver() const {
  return players.size() <= static_cast<unsigned long>(rules.getNum_players_left_to_end_game())
      || (rules.isTurnLimit() && turn_count >= rules.getTurn_limit());
}

Monopoly::Player& Monopoly::GameState::getCurrentPlayer() {
  return players[player_turn];
}

void Monopoly::GameState::make_move(Monopoly::Player& player, Monopoly::Move& move) {
  if (move.getAction() == MoveAction::rollDice) {
    int spacesToMove = diceRoller.getDiceRoll();
    int newLocation = spacesToMove + player.getSpaceOn().getSpaceNumber();
    int timesPastGo = newLocation / board.getNumSpaces();

    std::cout << player.getName() <<", you rolled a " << spacesToMove << std::endl;

    if(player.hasJailSentence() && player.getTurnsLeftInJail() > 0 && !diceRoller.multiplesRolled()) {
      player.serveTime();
      move.endsTurn = true;
      return;
    }

    // give the player their salary for passing go
    player.giveCash(board.getGoSalary() * timesPastGo);

    newLocation %= board.getNumSpaces();
    player.moveTo(*board.getSpacePtr(newLocation));

    if(rules.isAuction_properties() && player.isStartedAuction()) {
      Property* p = static_cast<Property*>(board.getSpacePtr(newLocation));
      AuctionManager auctionManager(*p, players, player_turn);
    }

    player.setStartedAuction(false);

    if(diceRoller.multiplesRolled() && Monopoly::Move::numRerolls < rules.get_max_doubles_reroll()) {
      move.endsTurn = false;
      Monopoly::Move::numRerolls += 1;
    } else {
      move.endsTurn = true;
      Monopoly::Move::numRerolls = 0;
    }

    if (player.getCash() < 0) {
      removeFromGame(player);
    }
  } else if (move.getAction() == MoveAction::leaveGame) {
    removeFromGame(player);
    move.endsTurn = true;
  } else if (move.getAction() == MoveAction::upgradeProperty) {
    player.upgradeProperties(board, rules);
    move.endsTurn = false;
  } else if (move.getAction() == MoveAction::sellHouseOrHotel) {
    player.sellUpgrades(board);
    move.endsTurn = false;
  }
}

void Monopoly::GameState::declareWinner() {
  int maxWorth = 0;

  //find the maximum net worth
  for (const auto& player : players) {
    int cur_player_worth = player.getNetWorth();
    if (cur_player_worth > maxWorth) {
      maxWorth = cur_player_worth;
    }
  }

  std::cout << "The winners are" << std::endl;
  for (const auto& player : players) {
    if (player.getNetWorth() == maxWorth) {
      std::cout << player.getName() << std::endl;
    }
  }

}

void Monopoly::GameState::changeTurn() {
  turn_count++;
  player_turn = (player_turn + 1) % players.size();
}

void Monopoly::GameState::removeFromGame(Monopoly::Player& player) {
  player.removeAllUpgrades(board, rules);

  // remove the player from the vector
  for (auto playerIt = players.cbegin(); playerIt != players.cend(); ++playerIt) {
    if (playerIt->getId() == player.getId()) {
      player.getSpaceOn().removePlayer(player);
      players.erase(playerIt);
      break;
    }
  }
  /*
  * update all pointers to players now that we've moved their locations in memory
  * Currently these are just the property owner pointers and the pointers on the spaces that point to who is on them
  * Has to be in a separate loop from the other because we need to get the players' new location in memory first
  */
  board.removeAllPlayers(); // remove all references from the spaces on the board to the players
  for (auto& rem_player :players) {
    rem_player.refreshReferencesTo();
  }

  //because we removed a player and everyone shifted over we need to
  player_turn--;

}

