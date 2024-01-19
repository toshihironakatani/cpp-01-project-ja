#include "display.h"
#include <iostream>

namespace display {

std::string car[] = {"→", "←", "↑", "↓"};

void start() {
  std::system("cls");
  std::cout << "Start Game" << std::endl;
  std::system("pause");
}

void _show_state(state::CarState current_state, int count) {
  std::cout << "=== State ===" << std::endl;
  std::cout << "speed: " << current_state.speed;
  std::cout << "   gas: " << current_state.gas_remain << " %";
  std::cout << "   money: " << current_state.money << " $";
  std::string temp_msg;
  if (current_state.has_passenger) {
    temp_msg = "Yes";
  } else {
    temp_msg = "No";
  }
  std::cout << "   passenger: " << temp_msg;
  std::cout << "   count: " << count  << std::endl;
  std::cout << std::endl;

  if (map::gas_stand.is_adjacent) {
    map::gas_stand.show_description();
    std::cout << std::endl;
  }
  if (map::bank.is_adjacent) {
    map::bank.show_description();
    std::cout << std::endl;
  }
  if (map::destination.is_adjacent) {
    map::destination.show_description();
    std::cout << std::endl;
  }
  if (map::passenger.is_adjacent) {
    map::passenger.show_description();
    std::cout << std::endl;
  }
}

void _show_map(state::CarState current_state) {
  std::string map_with_position[10];
  std::copy(std::begin(street_map), std::end(street_map),
            std::begin(map_with_position));

  map_with_position[current_state.y].replace(current_state.x, 1,
                                             car[current_state.direction]);

  for (std::string m : map_with_position) {
    std::cout << m << std::endl;
  }
  std::cout << std::endl;
}

std::string _get_sign(bool is_availabile) {
  if (is_availabile) {
    return "+";
  } else {
    return "-";
  }
}

void _show_command(state::CarState current_state, command::Availability availability) {
  std::cout << "=== Command ===" << std::endl;

  std::cout << " " << _get_sign(availability.continue_straight)
            << command::command_list[0] << std::endl;
  std::cout << " " << _get_sign(availability.turn_left)
            << command::command_list[1] << std::endl;
  std::cout << " " << _get_sign(availability.turn_right)
            << command::command_list[2] << std::endl;
  std::cout << " " << _get_sign(availability.accelerate)
            << command::command_list[3] << std::endl;
  std::cout << " " << _get_sign(availability.decelerate)
            << command::command_list[4] << std::endl;
  std::cout << " " << _get_sign(availability.drop_by)
            << command::command_list[5] << std::endl;
  std::cout << " +" << command::command_list[6] << std::endl;
  std::cout << std::endl;
  std::cout << "Input Command: ";
}

void update(state::CarState current_state, command::Availability availability, int count) {
  _show_state(current_state, count);
  _show_map(current_state);
  _show_command(current_state, availability);
}

void game_success(int count){
      std::system("cls");
      std::cout << "Arrive at the destination!" << std::endl;
      std::cout << "Your score is: " << count << std::endl;
      std::system("pause");
}

void invalid_input(){
      std::cout << "Invalid command. Input valid command." << std::endl;
      std::cout << "Input command: " << std::endl;
      std::system("pause");
}

void end() {
  std::system("cls");
  std::cout << "Finish Game" << std::endl;
}

} // namespace display
