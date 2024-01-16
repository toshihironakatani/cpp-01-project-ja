#include "state.h"
#include <iostream>

const int POSITION_XRANGE_LOW = 0;
const int POSITION_XRANGE_HIGH = MAP_SIZE_X;
const int POSITION_YRANGE_LOW = 0;
const int POSITION_YRANGE_HIGH = MAP_SIZE_Y;
const int GAME_OVER = -1;
const int GAME_SUCCESS = 10;

namespace state {

int update(CarState &current_state) {
  int temp_x = current_state.x;
  int temp_y = current_state.y;

  // update position
  switch (current_state.direction) {
  case XP:
    temp_x += current_state.speed;
    break;
  case XN:
    temp_x -= current_state.speed;
    break;
  case YP:
    temp_y -= current_state.speed;
    break;
  case YN:
    temp_y += current_state.speed;
    break;
  }

  if (temp_x < 0) {
    temp_x += MAP_SIZE_X;
  } else if (temp_x >= MAP_SIZE_X) {
    temp_x -= MAP_SIZE_X;
  }
  if (temp_y < 0) {
    temp_y += MAP_SIZE_Y;
  } else if (temp_y >= MAP_SIZE_Y) {
    temp_y -= MAP_SIZE_Y;
  }
  if (street_map[temp_y][temp_x] == '#') {
    std::system("cls");
    std::cout << "Crash! Game over..." << std::endl;
    std::system("pause");
    return GAME_OVER;
  } else {
    current_state.x = temp_x;
    current_state.y = temp_y;
  }

  // update gas
  current_state.gas_remain -= current_state.speed;
  if ((map::gas_stand.is_adjacent) && (current_state.drop_by == true)) {
    int total = current_state.gas_remain + current_state.money;
    if (total <= 100) {
      current_state.gas_remain += current_state.money;
      current_state.money = 0;
    } else {
      current_state.money -= (100 - current_state.gas_remain);
      current_state.gas_remain = 100;
    }
  }
  if (current_state.gas_remain <= 0) {
    std::system("cls");
    std::cout << "Gas is empty! Game over..." << std::endl;
    std::system("pause");
    return GAME_OVER;
  }

  // update money
  if ((map::bank.is_adjacent) && (current_state.drop_by == true)) {
    current_state.money += 10;
  }

  // update passenger state
  if ((map::passenger.is_adjacent) && (current_state.drop_by == true)) {
    current_state.has_passenger = true;
  }

  // arrive at destination
  if ((map::destination.is_adjacent) && (current_state.drop_by == true)) {
    if (current_state.has_passenger) {
      return GAME_SUCCESS;
    } else {
      std::cout << "You don't have a passenger. Pick them up.";
      std::system("pause");
    }
  }

  current_state.drop_by = false;
  return 0;
}

} // namespace state
