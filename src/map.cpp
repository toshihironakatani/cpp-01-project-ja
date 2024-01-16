#include "map.h"
#include <iostream>
#include <string>

const unsigned int MAP_SIZE_X = 20;
const unsigned int MAP_SIZE_Y = 10;
std::string street_map[MAP_SIZE_Y] = {
    "## #### #### #### ##", "## #### #### #### ##", "                    ",
    "## #### #### #### ##", "## #### #### #### ##", "## #### #### #### ##",
    "## #### #### #### ##", "                    ", "## #### #### #### ##",
    "## #### #### #### ##"};

namespace map {

Landmark gas_stand;
Landmark bank;
Landmark destination;
Landmark passenger;

void Landmark::initialize(int _x, int _y, std::string _mark, std::string _msg) {
  /*set position*/
  x = _x;
  y = _y;
  mark = _mark;

  /*set adjacent positoin*/
  // right
  adjacent_position[0][0] = x + 1;
  adjacent_position[0][1] = y;
  // over
  adjacent_position[1][0] = x;
  adjacent_position[1][1] = y + 1;
  // left
  adjacent_position[2][0] = x - 1;
  adjacent_position[2][1] = y;
  // under
  adjacent_position[3][0] = x;
  adjacent_position[3][1] = y - 1;

  /*set message*/
  msg = _msg;

  /*add_landmark_to_map*/
  street_map[y].replace(x, 1, mark);
}

void Landmark::judge_adjacent(unsigned int x, unsigned int y) {
  is_adjacent = false;
  for (int i = 0; i <= 3; ++i) {
    if ((adjacent_position[i][0] == x) && (adjacent_position[i][1] == y)) {
      is_adjacent = true;
    }
  }
}
void Landmark::show_description() { std::cout << msg << std::endl; }

void initialize() {
  std::string msg;

  msg = "You are in front of a gas station. If you drop by it, you can refuel.";
  gas_stand.initialize(6, 1, "G", msg);

  msg = "You are in front of a bank. If you drop by it, you can get money.";
  bank.initialize(1, 1, "B", msg);

  msg = "You are in front of the destination. If you drop by it with a passenger, you can succeed in this game.";
  destination.initialize(19, 8, "D", msg);

  msg = "You are in front of a passenger. If you drop by it, you can pick them up.";
  passenger.initialize(6, 4, "P", msg);
}

void update(unsigned int x, unsigned int y) {
  gas_stand.judge_adjacent(x, y);
  bank.judge_adjacent(x, y);
  destination.judge_adjacent(x, y);
  passenger.judge_adjacent(x, y);
}

} // namespace map
