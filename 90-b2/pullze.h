/* 2452098 计算机 赵崇治 */
#pragma once
#include "cmd_console_tools.h"

const int MAX_SIZE = 15;
const int MAX_HINTS = 8;





struct GameState
{
    int rows, cols;
    int grid[MAX_SIZE][MAX_SIZE];           // 原始数据 0-空 1-球
    int player[MAX_SIZE][MAX_SIZE];         // 玩家标记 0-未标记 1-标记有球 -1-标记无球

    int row_hints[MAX_SIZE][MAX_HINTS];     // 行提示
    int col_hints[MAX_SIZE][MAX_HINTS];     // 列提示
    int row_hint_count[MAX_SIZE];           // 行提示数量
    int col_hint_count[MAX_SIZE];           // 列提示数量

    int row_hints_player[MAX_SIZE][MAX_HINTS];     // 玩家行提示
    int col_hints_player[MAX_SIZE][MAX_HINTS];     // 玩家列提示
    int row_hint_count_player[MAX_SIZE];           // 玩家行提示数量
    int col_hint_count_player[MAX_SIZE];           // 玩家列提示数量

    bool cheat_mode;                        // 作弊模式
};





// pullze_base.cpp中的函数声明
void init_game(GameState& game, int rows, int cols);
void generate_balls(GameState& game);
void calculate_hints(GameState& game);
void calculate_player_hints(GameState& game);
void update_and_print_game(GameState& game, int row, int col,
                           bool is_cheat = false);
void print_game_text(const GameState& game,
                     bool show_hints = true,
                     bool show_answer = true);
bool check(GameState& game);
void play_text(GameState& game);





// pullze_console.cpp中的函数声明
void wait(int n = 5);
void draw_frame(const GameState& game, int op);
void draw_fake_GUI(GameState& game,
                   bool show_hints = true,
                   bool show_separator = true,
                   int op = -1);
void draw_game_area(GameState game, int op);
void draw_big(const GameState& game, int part, int mode);
void draw_big_ball(GameState& game, int x, int y, int i, int j);
void draw_big_cross(GameState& game, int x, int y, int i, int j);
void draw_big_space(GameState& game, int x, int y, int i, int j);
void handle_mouse_input(GameState& game, int op);
void loop_SMALL(GameState& game);
void loop_BIG(GameState& game);





// pullze_tools.cpp中的函数声明
int show_menu();
void get_size_input(int& rows, int& cols);
bool input_coordinate(int& row, int& col, int max_row, int max_col);
void show_status(const char* message);
void clear_status_area();