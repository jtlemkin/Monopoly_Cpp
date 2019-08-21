//
// Created by James Lemkin on 3/3/18.
//

#ifndef HOARDINGCPPVERSION_JAILSENTENCE_H
#define HOARDINGCPPVERSION_JAILSENTENCE_H
#include <string>
namespace Monopoly {
  class Player;

  class JailSentence {
   public:
    JailSentence(int prisonTermLength, int bail, Player* convict);
    void getBailDecision();
    void bailOut();
   protected:
    int turnsLeftInJail;
    int bail;
    Player* convict;
  };
}

#endif //HOARDINGCPPVERSION_JAILSENTENCE_H
