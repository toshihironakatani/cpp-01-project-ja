#pragma once

#include "state.h"
#include <string>

namespace command {

extern std::string command_list[7];

struct Availability {
  bool continue_straight;
  bool turn_left;
  bool turn_right;
  bool accelerate;
  bool decelerate;
  bool drop_by;
};

/*commands for game*/
void continue_straight();
void turn_left(enum DIRECTION &direction);
void turn_right(enum DIRECTION &direction);
void accelerate(int &speed);
void decelerate(int &speed);
void drop_by(bool &drop_by);

/*functions to use command*/
void judge_available_command(state::CarState current_state,
                             command::Availability &availability);
int get_user_command();
int execute_command(state::CarState &current_state,
                    command::Availability availability);

} // namespace command
