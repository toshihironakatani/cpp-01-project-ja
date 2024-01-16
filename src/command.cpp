#include "command.h"
#include <iostream>
#include <sstream>

namespace command {

std::string command_list[] = {
    "1: Continue straight", "2: Turn left", "3: Turn right", "4: Accelerate",
    "5: Decelerate",        "6: Drop by",   "exit: Finish"};

void continue_straight() {}

void turn_left(enum DIRECTION &direction) {
  switch (direction) {
  case XP:
    direction = YP;
    break;
  case XN:
    direction = YN;
    break;
  case YP:
    direction = XN;
    break;
  case YN:
    direction = XP;
    break;
  }
}

void turn_right(enum DIRECTION &direction) {
  switch (direction) {
  case XP:
    direction = YN;
    break;
  case XN:
    direction = YP;
    break;
  case YP:
    direction = XP;
    break;
  case YN:
    direction = XN;
    break;
  }
}

int get_user_command() {
  std::istringstream ss;
  std::string input;
  std::cin >> input;
  int cmd;

  if (input == "exit") {
    return 99;
  }

  ss = std::istringstream(input);
  ss >> cmd;

  return cmd;
}

int execute_command(state::CarState &current_state,
                    command::Availability availability) {
  bool is_invalid_command = true;

  while (is_invalid_command) {
    int cmd = get_user_command();

    switch (cmd) {
    case 1: {
      if (availability.continue_straight) {
        continue_straight();
        is_invalid_command = false;
      }
      break;
    }
    case 2: {
      if (availability.turn_left) {
        turn_left(current_state.direction);
        is_invalid_command = false;
      }
      break;
    }
    case 3: {
      if (availability.turn_right) {
        turn_right(current_state.direction);
        is_invalid_command = false;
      }
      break;
    }
    case 4: {
      if (availability.accelerate) {
        accelerate(current_state.speed);
        is_invalid_command = false;
      }
      break;
    }
    case 5: {
      if (availability.decelerate) {
        decelerate(current_state.speed);
        is_invalid_command = false;
      }
      break;
    }
    case 6: {
      if (availability.drop_by) {
        drop_by(current_state.drop_by);
        is_invalid_command = false;
      }
      break;
    }
    case 99: {
      return 99;
    }
    }

    if (is_invalid_command) {
      std::cout << "Invalid command. Input valid command." << std::endl;
      std::cout << "Input command: " << std::endl;
      std::system("pause");
    }
  }
  return 0;
}

void accelerate(int &speed) { speed += 1; }

void decelerate(int &speed) {
  if (speed > 0) {
    speed -= 1;
  }
}

void drop_by(bool &drop_by) { drop_by = true; }

void judge_available_command(state::CarState current_state,
                             command::Availability &availability) {
  if (current_state.speed == 0) {
    availability.continue_straight = false;
    availability.turn_left = true;
    availability.turn_right = true;
  }
  if (((map::gas_stand.is_adjacent) || (map::bank.is_adjacent) ||
       (map::destination.is_adjacent) ||
       (map::passenger.is_adjacent)) &&
      (current_state.speed == 0)) {
    availability.drop_by = true;
  }
}

} // namespace command
