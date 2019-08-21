//
// Created by mfbut on 1/23/2018.
//

#ifndef HOARDINGCPPVERSION_MOVE_H
#define HOARDINGCPPVERSION_MOVE_H

namespace Monopoly {
  enum class MoveAction { rollDice = 1, upgradeProperty = 2, sellHouseOrHotel = 3, leaveGame = 4, ERROR };
  class Move {
   public:
    Move();
    MoveAction getAction() const;
    Move(const int moveNumber);
    bool endsTurn;

    static int numRerolls;
   private:
    MoveAction action;
  };
}

#endif //HOARDINGCPPVERSION_MOVE_H
