//
// Created by mfbut on 1/20/2018.
//

#include "Board.h"
#include "Jail.h"
#include "GoToJail.h"

Monopoly::Board::Board(const std::string& boardFileName, const Rules& rules) {
  CSVReader boardFile(boardFileName);
  constexpr int num_lines_to_skip = 4;

  if (boardFile.good()) {
    boardFile.skip_field();
    const int numSpaces = boardFile.get_next_field_as_int();

    for (int i = 0; i < num_lines_to_skip; ++i) {
      boardFile.skip_line();
    }

    std::string space_type_string;
    SpaceType spaceType;

    for (int i = 0; i < numSpaces; ++i) {
      space_type_string = boardFile.get_next_field();
      spaceType = Space::get_space_type(space_type_string);
      if(spaceType == SpaceType::goSpace) {
        spacePtrs.emplace_back(std::make_unique<Go>(boardFile, i, rules));
      } else if(spaceType == SpaceType::propertySpace) {
        spacePtrs.emplace_back(std::make_unique<Property>(boardFile, i, rules));
      } else if(spaceType == SpaceType::freeParking) {
        spacePtrs.emplace_back(std::make_unique<FreeParking>(boardFile, i , rules));
      } else if(spaceType == SpaceType::payTheBank) {
        spacePtrs.emplace_back(std::make_unique<PayTheBank>(boardFile, i, rules));
      } else if(spaceType == SpaceType::jail) {
        spacePtrs.emplace_back(std::make_unique<Jail>(boardFile, i , rules));
      } else if (spaceType == SpaceType::goToJail) {
        spacePtrs.emplace_back(std::make_unique<GoToJail>(boardFile, i , rules));
      }
      //spacePtrs.emplace_back(Space::factory(boardFile, i, rules, Space::get_space_type(space_type_string)));
      //spaces.push_back(Space(boardFile, i, rules));
    }

    linkGoToJailsWithJails();

    numSets = calculateNumSet();

    Monopoly::Space::length_of_longest_space_name = calc_length_of_longest_space_name();
    Monopoly::Space::length_of_longest_space_name =
        Utility::max(Monopoly::Space::length_of_longest_space_name, std::string("Space Name").size());

    goSalary = getGoSpace()->getSalary();
  } else {
    std::cout << "Failed to open board file: " << boardFileName << std::endl;
  }
}

void Monopoly::Board::display() const {
  const std::string spaceNumber("Space Number");
  const std::string spaceName("Space Name");
  const std::string owner("Owner");
  const std::string upgrades("Upgrades");
  const std::string playersString("Players");
  const auto frmt_flags = std::cout.flags();
  std::cout.setf(std::ios::left);

  std::cout << spaceNumber; std::cout << " | ";
  std::cout.width(Space::length_of_longest_space_name);
  std::cout << spaceName; std::cout << " | ";

  std::cout.width(Space::length_of_longest_player_name);

  std::cout << owner; std::cout << " | ";
  std::cout << upgrades; std::cout << " | ";
  std::cout << playersString; std::cout << std::endl;

  int i = 0;
  for (const auto& space : spacePtrs) {
    std::cout.width(spaceNumber.size());
    std::cout << i << " | ";
    space->display();
    std::cout << std::endl;
    ++i;
  }
  std::cout.flags(frmt_flags);
}

unsigned long Monopoly::Board::calc_length_of_longest_space_name() const {
  std::vector<std::string> space_names;
  for (const auto& space : spacePtrs) {
    space_names.emplace_back(space->getName());
  }
  return Utility::get_max_string_length(space_names);
}

Monopoly::Space* Monopoly::Board::getSpacePtr(int spaceNum) {
  return spacePtrs[spaceNum].get();
}

Monopoly::Go* Monopoly::Board::getGoSpace() {
  for (auto& space : spacePtrs) {
    Go* go = dynamic_cast<Go*>(space.get());
    if (go) {
      return go;
    }
  }
  //this line should never execute
  //return *spacePtrs[0];
  return static_cast<Go*>(spacePtrs[0].get());
}

int Monopoly::Board::getNumSpaces() const {
  return static_cast<int>(spacePtrs.size());
}

const std::vector<std::unique_ptr<Monopoly::Space> >& Monopoly::Board::getSpaces() const {
  return spacePtrs;
}

void Monopoly::Board::removeAllPlayers() {
  for (auto& space : spacePtrs) {
    space->removeAllPlayers();
  }
}
int Monopoly::Board::getNumSets() const {
  return numSets;
}
int Monopoly::Board::getGoSalary() const {
  return goSalary;
}
std::vector<Monopoly::Property *> Monopoly::Board::getProperties() {
  std::vector<Monopoly::Property *> properties;
  for (const auto& space : spacePtrs) {
    Property* property = dynamic_cast<Property*>(space.get());
    if (property) {
      properties.push_back(property);
    }
  }

  return properties;
}
int Monopoly::Board::calculateNumSet() {
  if(getProperties().empty()) {
    return 0;
  } else {
    return numSets = getProperties().back()->getSetId() + 1;
  }
}
void Monopoly::Board::linkGoToJailsWithJails() {
  auto goToJails = getGoToJails();

  for(const auto& goToJail: goToJails) {
    goToJail->setJailPtr(static_cast<Jail*>(getSpacePtr(goToJail->getIndexOfSpaceToGoTo())));
  }
}
std::vector<Monopoly::GoToJail *> Monopoly::Board::getGoToJails() {
  std::vector<Monopoly::GoToJail *> goToJails;

  for (const auto& space : spacePtrs) {
    auto goToJail = dynamic_cast<GoToJail*>(space.get());
    if (goToJail) {
      goToJails.push_back(goToJail);
    }
  }

  return goToJails;
}

