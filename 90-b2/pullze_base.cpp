/* 2452098 计算机 赵崇治 */

#include <iostream>
#include <iomanip>
#include "pullze.h"
using namespace std;

void init_game(GameState& game, int rows, int cols)
{
    game.rows = rows;
    game.cols = cols;
    game.cheat_mode = false;
    game.with_separator = false;

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            game.grid[i][j] = 0;
            game.player[i][j] = 0;
        }
        game.row_hint_count[i] = 0;
        game.col_hint_count[i] = 0;
        for (int k = 0; k < MAX_HINTS; k++) {
            game.row_hints[i][k] = 0;
            game.col_hints[i][k] = 0;
        }
    }
}

void generate_balls(GameState& game)
{
    int total_cells = game.rows * game.cols; // cell就是小方格的意思
    int ball_count = (total_cells + 1) / 2; // 上取整

    int tot = 0;
    while (tot < ball_count) {
        int row = rand() % game.rows;
        int col = rand() % game.cols;
        if (game.grid[row][col] == 0) {
            game.grid[row][col] = 1;
            tot++;
        }
    }
}

void calculate_hints(GameState& game)
{
    // 计算行提示
    for (int i = 0; i < game.rows; i++) {
        int count = 0;
        int len = 0;

        for (int j = 0; j < game.cols; j++) {
            if (game.grid[i][j] == 1) {
                len++;
            }
            else {
                if (len > 0) {
                    game.row_hints[i][count++] = len;
                    len = 0; // 断开上一段
                }
            }
        }
        if (len > 0) {
            game.row_hints[i][count++] = len;
        }
        game.row_hint_count[i] = count; // 段数
    }

    // 计算列提示
    for (int j = 0; j < game.cols; j++) {
        int count = 0;
        int len = 0;

        for (int i = 0; i < game.rows; i++) {
            if (game.grid[i][j] == 1) {
                len++;
            }
            else {
                if (len > 0) {
                    game.col_hints[j][count++] = len;
                    len = 0; // 断开上一段
                }
            }
        }
        if (len > 0) {
            game.col_hints[j][count++] = len;
        }
        game.col_hint_count[j] = count; // 段数
    }
}

// 更新玩家选择并打印当前棋局
void update_and_print_game(GameState& game, int row, int col,
                           bool is_cheat)
{
    if (game.player[row][col] != 1) {
        game.player[row][col] = 1;
    }
    else {
        game.player[row][col] = -1;
    }
    
    if(row==-2)
        cout<< "\n\n\n输入Z / z后：\n";
    else
        cout << "\n\n输入" << (char)(row + 'A') << (char)(col + 'a') << "后：\n";
    
    // 计算提示区域的大小
    int hint_cols = 0;
    for (int j = 0; j < game.rows; j++) {
        if (game.row_hint_count[j] > hint_cols) {
            hint_cols = game.row_hint_count[j];
        }
    } // 预留列数
    
    // 打印上边框
    for (int j = 0; j <= hint_cols; j++) {
        cout << "--";
    }
    cout << "-+";
    for (int i = 1; i <= game.rows / 5; i++) {
        cout << "------";
        cout << "-----+";
    }
    cout << endl;
    
    int hint_rows = 0;
    for (int j = 0; j < game.cols; j++) {
        if (game.col_hint_count[j] > hint_rows) {
            hint_rows = game.col_hint_count[j];
        }
    } // 预留行数
    
    // 打印列提示
    for (int row = 0; row < hint_rows; row++) {
        cout << " ";
        for (int j = 0; j <= hint_cols; j++)
            cout << "  ";
        cout << "|"; // 每行前导空白
        for (int j = 0; j < game.cols; j++) {
            if (j > 0 && j % 5 == 0)
                cout << " |";
            int hint_idx = row - (hint_rows - game.col_hint_count[j]);
            if (hint_idx >= 0 && hint_idx < game.col_hint_count[j]) {
                if (game.col_hints[j][hint_idx] < 10)
                    cout << " ";
                cout << game.col_hints[j][hint_idx];
            }
            else {
                cout << "  ";
            }
        }
        cout << " | " << endl;
    }
    
    // 分隔线
    for (int j = 0; j <= hint_cols; j++) {
        cout << "--";
    }
    cout << "-+";
    for (int i = 1; i <= game.rows / 5; i++) {
        cout << "------";
        cout << "-----+";
    }
    cout << endl;
    
    // 打印列标签
    for (int j = 0; j <= hint_cols; j++) {
        cout << "  ";
    }
    cout << " | ";
    for (int j = 0; j < game.cols; j++) {
        if (j > 0 && j % 5 == 0) cout << "| ";
        cout << char('a' + j) << " ";
    }
    cout << "| " << endl;
    
    // 分隔线
    for (int j = 0; j < hint_cols; j++) {
        cout << "--";
    }
    cout << "-+-+";
    for (int i = 1; i <= game.rows / 5; i++) {
        cout << "------";
        cout << "-----+";
    }
    cout << endl;
    
    // 打印行提示和棋盘内容
    for (int segment = 0; segment < (game.rows + 4) / 5; segment++) { // 计算需要多少段，上取整
        for (int j_in_segment = 0; j_in_segment < 5 && (segment * 5 + j_in_segment) < game.rows; j_in_segment++) {
            int j = segment * 5 + j_in_segment; // 实际的行索引
            
            // 打印行提示
            for (int col = 0; col < hint_cols; col++) {
                int hint_idx = col - (hint_cols - game.row_hint_count[j]);
                if (hint_idx >= 0 && hint_idx < game.row_hint_count[j]) {
                    break;
                }
                else {
                    cout << "  ";
                }
            }
            
            // 打印行标识和内容
            int i = 0;
            while (game.row_hints[j][i] > 0) {
                if (game.row_hints[j][i] < 10)
                    cout << " ";
                cout << game.row_hints[j][i];
                i++;
            }
            cout << " |" << char('A' + j) << "| ";
            for (int i = 0; i < game.cols; i++) {
                // 根据内部数组显示玩家选择
                if ((game.player[j][i] == 1 && !is_cheat)
                  || (is_cheat && game.player[j][i] == 1 && game.grid[j][i] == 1)) {
                    cct_setcolor(14, 8);
                    cout << "0"; // 玩家选择的位置显示0
                    cct_setcolor();
                    cout << " ";
                }
                else if(is_cheat && game.player[j][i] == 1 && game.grid[j][i] == 0) {
                    cct_setcolor(14, 8);
                    cout << "X"; // 玩家选择的位置显示0
                    cct_setcolor();
                    cout << " ";
                }
                else if (is_cheat && game.player[j][i] == 0 && game.grid[j][i] == 1) {
                    cout << "0 ";
                }
                else {
                    cout << "  "; // 未选择的位置显示空格
                }
                if (i > 0 && i % 5 == 4) {
                    cout << "| ";
                }
            }
            cout << endl;
        }
        
        // 每段结束后打印分隔线（除非是最后一段）
        if (segment < (game.rows + 4) / 5 - 1) {
            for (int j = 0; j < hint_cols; j++) {
                cout << "--";
            }
            cout << "-+-+";
            for (int i = 1; i <= game.rows / 5; i++) {
                cout << "------";
                cout << "-----+";
            }
            cout << endl;
        }
    }
    
    for (int j = 0; j < hint_cols; j++) {
        cout << "--";
    }
    cout << "-+-+";
    for (int i = 1; i <= game.rows / 5; i++) {
        cout << "------";
        cout << "-----+";
    }
    cout << endl;
}

void print_game_text(const GameState& game, bool show_hints,
                     bool show_answer)
{
    cout << "初始数组:\n";

    if (show_hints) {
        int hint_cols = 0;
        for (int j = 0; j < game.rows; j++) {
            if (game.row_hint_count[j] > hint_cols) {
                hint_cols = game.row_hint_count[j];
            }
        } // 预留列数

        for (int j = 0; j <= hint_cols; j++) {
            cout << "--";
        }
        cout << "-+";
        for (int i = 1; i <= game.rows / 5; i++) {
            cout << "------";
            cout << "-----+";
        }
        cout << endl;

        int hint_rows = 0;
        for (int j = 0; j < game.cols; j++) {
            if (game.col_hint_count[j] > hint_rows) {
                hint_rows = game.col_hint_count[j];
            }
        } // 预留行数

        // 打印列提示
        for (int row = 0; row < hint_rows; row++) {
            cout << " ";
            for (int j = 0; j <= hint_cols; j++)
                cout << "  ";
            cout << "|"; // 每行前导空白
            for (int j = 0; j < game.cols; j++) {
                if (j > 0 && j % 5 == 0)
                    cout << " |";
                int hint_idx = row - (hint_rows - game.col_hint_count[j]);
                if (hint_idx >= 0 && hint_idx < game.col_hint_count[j]) {
                    if (game.col_hints[j][hint_idx] < 10)
                        cout << " ";
                    cout << game.col_hints[j][hint_idx];
                }
                else {
                    cout << "  ";
                }
            }
            cout << " | " << endl;
        }

        // 分隔线
        for (int j = 0; j <= hint_cols; j++) {
            cout << "--";
        }
        cout << "-+";
        for (int i = 1; i <= game.rows / 5; i++) {
            cout << "------";
            cout << "-----+";
        }
        cout << endl;

        for (int j = 0; j <= hint_cols; j++) {
            cout << "  ";
        }
        cout << " | ";
        for (int j = 0; j < game.cols; j++) {
            if (j > 0 && j % 5 == 0) cout << "| ";
            cout << char('a' + j) << " ";
        }
        cout << "| " << endl;

        for (int j = 0; j < hint_cols; j++) {
            cout << "--";
        }
        cout << "-+-+";
        for (int i = 1; i <= game.rows / 5; i++) {
            cout << "------";
            cout << "-----+";
        }
        cout << endl;

        // 打印行提示
        for (int segment = 0; segment < (game.rows + 4) / 5; segment++) { // 计算需要多少段，上取整
            for (int j_in_segment = 0; j_in_segment < 5 && (segment * 5 + j_in_segment) < game.rows; j_in_segment++) {
                int j = segment * 5 + j_in_segment; // 实际的行索引
                
                // 打印行提示
                for (int col = 0; col < hint_cols; col++) {
                    int hint_idx = col - (hint_cols - game.row_hint_count[j]);
                    if (hint_idx >= 0 && hint_idx < game.row_hint_count[j]) {
                        break;
                    }
                    else {
                        cout << "  ";
                    }
                }
                
                // 打印行标识和内容
                int i = 0;
                while (game.row_hints[j][i] > 0) {
                    if (game.row_hints[j][i] < 10)
                        cout << " ";
                    cout << game.row_hints[j][i];
                    i++;
                }
                cout << " |" << char('A' + j) << "| ";
                for (int i = 0; i < game.cols; i++) {
                    if (game.grid[j][i]&&show_answer) {
                        cout << "0 ";
                    }
                    else {
                        cout << "  ";
                    }
                    if (i > 0 && i % 5 == 4) {
                        cout << "| ";
                    }
                }
                cout << endl;
            }
            
            // 每段结束后打印分隔线（除非是最后一段）
            if (segment < (game.rows + 4) / 5 - 1) {
                for (int j = 0; j < hint_cols; j++) {
                    cout << "--";
                }
                cout << "-+-+";
                for (int i = 1; i <= game.rows / 5; i++) {
                    cout << "------";
                    cout << "-----+";
                }
                cout << endl;
            }
        }
        for (int j = 0; j < hint_cols; j++) {
            cout << "--";
        }
        cout << "-+-+";
        for (int i = 1; i <= game.rows / 5; i++) {
            cout << "------";
            cout << "-----+";
        }
        cout << endl;
    }

    else {
        cout << "+-+";
        for (int i = 1; i <= game.rows / 5; i++) {
            cout << "------";
            cout << "-----+";
        }
        cout << endl;

        cout << "| | ";
        
        for (int j = 0; j < game.cols; j++) {
            if (j > 0 && j % 5 == 0)
                cout << "| ";
            cout << char('a' + j) << " ";
        }
        cout << "| " << endl;

        cout << "+-+";
        for (int i = 1; i <= game.rows / 5; i++) {
            cout << "------";
            cout << "-----+";
        }
        cout << endl;
        
        // 打印游戏区域内容
        for (int segment = 0; segment < (game.rows + 4) / 5; segment++) { // 计算需要多少段，上取整
            for (int j_in_segment = 0; j_in_segment < 5 && (segment * 5 + j_in_segment) < game.rows; j_in_segment++) {
                int j = segment * 5 + j_in_segment; // 实际的行索引
                
                cout << "|" << char('A' + j) << "| ";
                for (int i = 0; i < game.cols; i++) {
                    if (show_answer&&game.grid[j][i]) {
                        cout << "0 ";
                    }
                    else {
                        cout << "  ";
                    }
                    if (i > 0 && i % 5 == 4) {
                        cout << "| ";
                    }
                }
                cout << endl;
            }
            
            // 每段结束后打印分隔线（除非是最后一段）
            if (segment < (game.rows + 4) / 5 - 1) {
                cout << "+-+";
                for (int i = 1; i <= game.rows / 5; i++) {
                    cout << "------";
                    cout << "-----+";
                }
                cout << endl;
            }
        }
        
        // 最后一行分隔线
        cout << "+-+";
        for (int i = 1; i <= game.rows / 5; i++) {
            cout << "------";
            cout << "-----+";
        }
        cout << endl;
    }
}

void play_text(GameState& game)
{
    while (1) {
        int row = 0;
        int col = 0;
        if (input_coordinate(row, col, game.rows, game.cols)) {
            if (row == -2) {
                update_and_print_game(game, row, col, true); // cheat
            }
            else if (row == -1) {
                cout << "Y / y\n";
                for (int i = 0; i < game.rows; i++) {
                    for (int j = 0; j < game.cols; j++) {
                        if (game.grid[i][j] != game.player[i][j]) {
                            cout << "\n\n提交错误, [" << (char)('A' + i) << "]行[" << (char)('a' + j) << "]列不符合要求";
                            i = game.rows;
                            break;
                        }
                    }
                }
            }
            else {
                update_and_print_game(game, row, col);
            }
        }
        else {
            break;
        }
    }
}

bool check_win(const GameState& game)
{
    for (int i = 0; i < game.rows; i++) {
        for (int j = 0; j < game.cols; j++) {
            if (game.grid[i][j] == 1 && game.player[i][j] != 1) {
                return false;
            }
            if (game.grid[i][j] == 0 && game.player[i][j] == 1) {
                return false;
            }
        }
    }
    return true;
}