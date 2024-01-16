#pragma once

#include "state.h"
#include <string>

extern const unsigned int MAP_SIZE_X;
extern const unsigned int MAP_SIZE_Y;
extern std::string street_map[10];

namespace map {
  //state::CarState test;

  void update(unsigned int x, unsigned int y);
  void initialize();

  class Landmark {

  public:
    unsigned int x;
    unsigned int y;
    std::string mark;
    int adjacent_position[4][2];
    std::string msg;
    bool is_adjacent;

    void initialize(int x, int y, std::string _mark, std::string _msg);
    void execute_event();
    void set_adjacent_position();
    void judge_adjacent(unsigned int x, unsigned int y);
    void show_description();
  };

  extern Landmark gas_stand;
  extern Landmark bank;
  extern Landmark destination;
  extern Landmark passenger;

} // namespace map
