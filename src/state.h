#pragma once
#include "map.h"

enum DIRECTION { XP, XN, YP, YN }; // TODO: 適切な場所に移動
extern const int GAME_OVER;
extern const int GAME_SUCCESS;

namespace state {

struct CarState {
  unsigned int x;
  unsigned int y;
  enum DIRECTION direction;
  int speed;
  int gas_remain;
  unsigned int money;
  bool drop_by;
  bool has_passenger;
};

extern CarState current_state;
int update(CarState &current_state);

} // namespace state
