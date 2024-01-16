
#include "command.h"
#include "display.h"
#include "map.h"
#include "state.h"
#include <iostream>
#include <string>
#include <windows.h>

int main() {
  int command_ret;
  int game_status;
  int turn_count = 0;
  state::CarState current_state = {0, 2, XP, 0, 100, 0, false, false};

  map::initialize();
  display::start();

  while (true) {
    command::Availability availability = {true, false, false,
                                          true, true,  false};
    std::system("cls");
    command::judge_available_command(current_state,
                                     availability); // 選択可能なコマンドを判定
    display::update(current_state, availability, turn_count); // 画面表示を更新
    command_ret = command::execute_command(current_state, availability); // コマンド入力と実行
    if (command_ret == 99) {
      break;
    }
    turn_count++;
    game_status = state::update(current_state); // 車両状態を更新

    if (game_status == GAME_OVER) {
      // game over
      break;
    }

    if (game_status == GAME_SUCCESS) {
      // game success
      std::system("cls");
      std::cout << "Arrive at the destination!" << std::endl;
      std::cout << "Your score is: " << turn_count << std::endl;
      std::system("pause");
      break;
    }
    map::update(current_state.x, current_state.y); // 地図状態を更新
  }
  display::end();

  return 0;
}
