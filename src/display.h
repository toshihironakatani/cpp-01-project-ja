#pragma once
#include "state.h"
#include "command.h"
#include <string>

namespace display {
  void start();
  void update(state::CarState current_state, command::Availability availability, int count);
  void game_success(int count);
  void invalid_input();
  void end();
}
