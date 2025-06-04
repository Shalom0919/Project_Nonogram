/* 2452098 计算机 赵崇治 */

#include <iostream>
#include <Windows.h>
#include "pullze.h"
using namespace std;

void wait(int n) {
    Sleep(n);
}

void draw_frame(const GameState& game, int op)
{
    cct_cls();
    if (op == 4) {
        cct_setconsoleborder(game.rows * 2 + 7, 23);
        cct_setfontsize("新宋体", 34);

        cout << "\n    ";
        for (int i = 0; i < game.cols; i++) {
            cout << (char)('a' + i) << " ";
            wait();
        }
        cout << "\n  ";
        wait();

        cct_setcolor(COLOR_HWHITE, 0);
        cout << "╔";
        wait();
        for (int i = 0; i < game.cols; i++) {
            cout << "══";
            wait();
        }
        cout << "═╗ \n";
        wait();

        for (int i = 0; i < game.rows; i++) {
            cct_setcolor();
            cout << (char)('A' + i) << " ";
            wait();
            cct_setcolor(COLOR_HWHITE, 0);
            cout << "║ ";
            wait();
            for (int j = 0; j < game.cols - 1; j++) {
                cout << "  ";
                wait();
            }
            cout << "  ║ \n";
            wait();
        }

        cct_setcolor();
        cout << "  ";
        wait();
        cct_setcolor(COLOR_HWHITE, 0);
        cout << "╚";
        wait();
        for (int i = 0; i < game.cols; i++) {
            cout << "══";
            wait();
        }
        cout << "═╝ \n";
    }
    
    if (op == 8) {
        cct_setconsoleborder(game.rows * 5 + 7, 23);
        cct_setfontsize("新宋体", 26);

        for (int i = 0; i < game.cols; i++) {
            cout << (char)('a' + i) << " ";
            wait();
        }
        cout << "\n  ";
        wait();

        cct_setcolor(COLOR_HWHITE, 0);
        cout << "╔";
        wait();
        for (int i = 0; i < game.cols; i++) {
            cout << "══";
            wait();
        }
        cout << "═╗ \n";
        wait();

        for (int i = 0; i < game.rows; i++) {
            cct_setcolor();
            cout << (char)('A' + i) << " ";
            wait();
            cct_setcolor(COLOR_HWHITE, 0);
            cout << "║ ";
            wait();
            for (int j = 0; j < game.cols - 1; j++) {
                cout << "  ";
                wait();
            }
            cout << "  ║ \n";
            wait();
        }

        cct_setcolor();
        cout << "  ";
        wait();
        cct_setcolor(COLOR_HWHITE, 0);
        cout << "╚";
        wait();
        for (int i = 0; i < game.cols; i++) {
            cout << "══";
            wait();
        }
        cout << "═╝ \n";
    }

    cct_setcolor();
}

void draw_fake_GUI(GameState& game, 
                   bool show_hint,
                   bool show_seperator,
                   int op) {

    cct_setfontsize("新宋体", 28 - game.rows / 5 * 2);
    cct_cls();
    if (op == 6) {
        cout << "测试键盘/鼠标左键/右键，回车退出\n";
    }
    else if (op == 7) {
        cout << "左键选〇/右键选×，回车提交，Q/q结束\n";
    }

    int hint_cols = 0;
    for (int j = 0; j < game.rows; j++) {
        if (game.row_hint_count[j] > hint_cols) {
            hint_cols = game.row_hint_count[j];
        }
    } // 预留列数

    for (int j = 0; j <= hint_cols; j++) {
        cout << "  ";
    }
    cout << "  ";
    cct_setcolor(COLOR_HWHITE, 0);
    cout << "╔";
    for (int i = 1; i < game.rows / 5 * 2; i++) {
        cout << "═════";
    }
    cout << "══════╗ " << endl;

    int hint_rows = 0;
    for (int j = 0; j < game.cols; j++) {
        if (game.col_hint_count[j] > hint_rows) {
            hint_rows = game.col_hint_count[j];
        }
    } // 预留行数

    // 打印列提示
    for (int row = 0; row < hint_rows; row++) {
        cct_setcolor();
        cout << "  ";
        for (int j = 0; j <= hint_cols; j++)
            cout << "  ";
        cct_setcolor(COLOR_HWHITE, 0);
        cout << "║ "; // 每行前导空白
        for (int j = 0; j < game.cols; j++) {
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
        cout << "║ " << endl;
    }

    // 分隔线
    cct_setcolor();
    for (int j = 0; j <= hint_cols; j++) {
        cout << "  ";
    }
    cout << "  ";
    cct_setcolor(COLOR_HWHITE, 0);
    cout << "╠";
    for (int i = 1; i < game.rows / 5 * 2; i++) {
        cout << "═════";
    }
    cout << "══════╣ " << endl;

    cct_setcolor();
    for (int j = 0; j <= hint_cols; j++) {
        cout << "  ";
    }
    cout << "  ";
    cct_setcolor(COLOR_HWHITE, 0);
    cout << "║ ";
    for (int j = 0; j < game.cols; j++) {
        cout << " " << char('a' + j);
    }
    cout << "║ " << endl;

    cout << "╔";
    for (int j = 0; j < hint_cols; j++) {
        cout << "══";
    }
    cout << "╦══╬";
    for (int i = 1; i < game.rows / 5 * 2; i++) {
        cout << "═════";
    }
    cout << "══════╣ " << endl;

    // 打印行提示
    for (int segment = 0; segment < (game.rows + 4) / 5; segment++) { // 计算需要多少段，上取整
        for (int j_in_segment = 0; j_in_segment < 5 && (segment * 5 + j_in_segment) < game.rows; j_in_segment++) {
            int j = segment * 5 + j_in_segment; // 实际的行索引
            cout << "║";
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
            cout << "║ " << char('A' + j) << "║ ";
            for (int i = 0; i < game.cols; i++) {
                if (game.grid[j][i]/* && show_answer*/) {
                    cout << "  ";
                }
                else {
                    cout << "  ";
                }
                if (i == game.cols - 1) {
                    cout << "║ ";
                }
            }
            cout << endl;
        }
    }
    cout << "╚══";
    for (int j = 1; j < hint_cols; j++) {
        cout << "══";
    }
    cout << "╩══╩";
    for (int i = 1; i < game.rows / 5 * 2; i++) {
        cout << "═════";
    }
    cout << "══════╝ " << endl;

    cct_setcolor();
}

void draw_game_area(const GameState& game, int op)
{
    int x = 0;
    int y = 0;
    int hint_cols = 0;
    for (int j = 0; j < game.rows; j++) {
        if (game.row_hint_count[j] > hint_cols) {
            hint_cols = game.row_hint_count[j];
        }
    } // 预留列数

    int hint_rows = 0;
    for (int j = 0; j < game.cols; j++) {
        if (game.col_hint_count[j] > hint_rows) {
            hint_rows = game.col_hint_count[j];
        }
    } // 预留行数

    if (op == 4) {
        x = 4;
        y = 3;
    }
    else if (op == 5) {
        x = hint_cols * 2 + 6;
        y = hint_rows + 4;
    }
    else if (op == 6) {
        x = hint_cols * 2 + 6;
        y = hint_rows + 5;
    }
    else {
        ;
    }
    for (int i = 0; i < game.rows; i++) {
        cct_gotoxy(x, i + y);
        for (int j = 0; j < game.cols; j++) {
            if (game.grid[i][j] == 1) {
                if (op != 7) {
                    cct_setcolor(9, 0);
                    cout << "〇";
                }
            }
            else {
                cct_setcolor(COLOR_HWHITE, 0);
                cout << "  ";
            }
        }
    }
    cct_setcolor();
    cct_gotoxy(0, hint_rows + game.rows + 7);
}

void handle_mouse_input(GameState& game, int op)
{
    cct_enable_mouse();
    cct_setcursor(CURSOR_INVISIBLE);

    int hint_cols = 0;
    for (int j = 0; j < game.rows; j++) {
        if (game.row_hint_count[j] > hint_cols) {
            hint_cols = game.row_hint_count[j];
        }
    } // 预留列数

    int hint_rows = 0;
    for (int j = 0; j < game.cols; j++) {
        if (game.col_hint_count[j] > hint_rows) {
            hint_rows = game.col_hint_count[j];
        }
    } // 预留行数

    int mx, my, maction, keycode1, keycode2;
    while (true) {
        int ret = cct_read_keyboard_and_mouse(mx, my, maction, keycode1, keycode2);
        int grid_oldx = -1024;
        int grid_oldy = -1024;
        int grid_x = -1024; // 单独处理0附近的截断向0取整问题
        if(mx - hint_cols * 2 - 6 >= 0)
            grid_x= (mx - hint_cols * 2 - 6) / 2;
        int grid_y = my - hint_rows - 5;
        if (ret == CCT_MOUSE_EVENT) {
            cct_showstr(9, hint_rows + game.rows + 7, "[当前光标] ");
            if (grid_x >= 0 && grid_x < game.cols && grid_y >= 0 && grid_y < game.rows) {
                if (maction == MOUSE_ONLY_MOVED && (grid_x != grid_oldx || grid_y != grid_oldy)) {
                    char r[2];
                    r[0] = 'A' + grid_y;
                    r[1] = '\0';
                    char l[2];
                    l[0] = 'a' + grid_x;
                    l[1] = '\0';
                    cct_showstr(20, hint_rows + game.rows + 7, r);
                    cct_showstr(21, hint_rows + game.rows + 7, "行");
                    cct_showstr(23, hint_rows + game.rows + 7, l);
                    cct_showstr(24, hint_rows + game.rows + 7, "列              ");
                    grid_oldx = grid_x;
                    grid_oldy = grid_y;
                }
                else if (maction == MOUSE_LEFT_BUTTON_CLICK) {
                    cct_showstr(9, hint_rows + game.rows + 7, "[读到左键]                 ");
                    char r[2];
                    r[0] = 'A' + grid_y;
                    r[1] = '\0';
                    char l[2];
                    l[0] = 'a' + grid_x;
                    l[1] = '\0';
                    cct_showstr(20, hint_rows + game.rows + 7, r);
                    cct_showstr(21, hint_rows + game.rows + 7, "行");
                    cct_showstr(23, hint_rows + game.rows + 7, l);
                    cct_showstr(24, hint_rows + game.rows + 7, "列              ");
                    cout << "\n         窗口：" << mx << "行 " << my << "列\n";
                    break;
                }
                else if (maction == MOUSE_RIGHT_BUTTON_CLICK) {
                    cct_showstr(9, hint_rows + game.rows + 7, "[读到右键]                 ");
                    cout << "\n         窗口：" << mx << "行 " << my << "列\n";
                    break;
                }
            }
            else {
                cct_showstr(20, hint_rows + game.rows + 7, "位置非法         ");
            }
        }
        else if (ret == CCT_KEYBOARD_EVENT) {
            if (keycode1 == 13) {
                cct_showstr(9, hint_rows + game.rows + 7, "[读到回车键]                 ");
                break;
            }
            else {
                cct_showstr(9, hint_rows + game.rows + 7, "[读到键码] ");
                cout << keycode1 << "/" << keycode2;
                if (keycode1 == 224) {
                    cout << " [方向键]";
                } 
                else {
                    cout << "          ";
                }
            }
        }
    }
    
    cct_disable_mouse();
    cct_setcursor(CURSOR_SHOWING);
}

void console_game_loop(GameState& game)
{
    cct_enable_mouse();
    cct_setcursor(CURSOR_INVISIBLE);

    int hint_cols = 0;
    for (int j = 0; j < game.rows; j++) {
        if (game.row_hint_count[j] > hint_cols) {
            hint_cols = game.row_hint_count[j];
        }
    } // 预留列数

    int hint_rows = 0;
    for (int j = 0; j < game.cols; j++) {
        if (game.col_hint_count[j] > hint_rows) {
            hint_rows = game.col_hint_count[j];
        }
    } // 预留行数

    int mx, my, maction, keycode1, keycode2;
    while (true) {
        int ret = cct_read_keyboard_and_mouse(mx, my, maction, keycode1, keycode2);
        int grid_oldx = -1024;
        int grid_oldy = -1024;
        int grid_x = -1024; // 单独处理0附近的截断向0取整问题
        if (mx - hint_cols * 2 - 6 >= 0)
            grid_x = (mx - hint_cols * 2 - 6) / 2;
        int grid_y = my - hint_rows - 5;
        if (ret == CCT_MOUSE_EVENT) {
            cct_showstr(9, hint_rows + game.rows + 7, "[当前光标] ");
            if (grid_x >= 0 && grid_x < game.cols && grid_y >= 0 && grid_y < game.rows) {
                if (maction == MOUSE_ONLY_MOVED && (grid_x != grid_oldx || grid_y != grid_oldy)) {
                    char r[2];
                    r[0] = 'A' + grid_y;
                    r[1] = '\0';
                    char l[2];
                    l[0] = 'a' + grid_x;
                    l[1] = '\0';
                    cct_showstr(20, hint_rows + game.rows + 7, r);
                    cct_showstr(21, hint_rows + game.rows + 7, "行");
                    cct_showstr(23, hint_rows + game.rows + 7, l);
                    cct_showstr(24, hint_rows + game.rows + 7, "列                         ");
                    grid_oldx = grid_x;
                    grid_oldy = grid_y;
                }
                else if (maction == MOUSE_LEFT_BUTTON_CLICK) {
                    cct_showstr(9, hint_rows + game.rows + 7, "[读到左键]                 ");
                    char r[2];
                    r[0] = 'A' + grid_y;
                    r[1] = '\0';
                    char l[2];
                    l[0] = 'a' + grid_x;
                    l[1] = '\0';
                    cct_showstr(20, hint_rows + game.rows + 7, r);
                    cct_showstr(21, hint_rows + game.rows + 7, "行");
                    cct_showstr(23, hint_rows + game.rows + 7, l);
                    cct_showstr(24, hint_rows + game.rows + 7, "列                         ");
                    if (game.player[grid_y][grid_x] != 1) {
                        cct_gotoxy(mx - mx % 2, my);
                        cct_setcolor(9, 0);
                        cout << "〇";
                        cct_setcolor();
                        game.player[grid_y][grid_x] = 1;
                    }
                    else {
                        cct_gotoxy(mx - mx % 2, my);
                        cct_setcolor(COLOR_HWHITE, 0);
                        cout << "  ";
                        cct_setcolor();
                        game.player[grid_y][grid_x] = 0;
                    }
                }
                else if (maction == MOUSE_RIGHT_BUTTON_CLICK) {
                    cct_showstr(9, hint_rows + game.rows + 7, "[读到右键]                 ");
                    cout << "\n         窗口：" << mx << "行 " << my << "列\n";
                    if (game.player[grid_y][grid_x] != -1) {
                        cct_gotoxy(mx - mx % 2, my);
                        cct_setcolor(COLOR_HRED, COLOR_BLACK);
                        cout << "×";
                        cct_setcolor();
                        game.player[grid_y][grid_x] = -1;
                    }
                    else {
                        cct_gotoxy(mx - mx % 2, my);
                        cct_setcolor(COLOR_HWHITE, 0);
                        cout << "  ";
                        cct_setcolor();
                        game.player[grid_y][grid_x] = 0;
                    }
                }
            }
            else {
                cct_showstr(20, hint_rows + game.rows + 7, "位置非法         ");
            }
        }
        else if (ret == CCT_KEYBOARD_EVENT) {
            if (keycode1 == 13) {
                cct_showstr(9, hint_rows + game.rows + 7, "[检查提交] ");
                if (check_win(game)) {
                    cct_showstr(9, hint_rows + game.rows + 7, "[提交成功]                                 ");
                    break;
                }
                else {
                    for (int i = 0; i < game.rows; i++) {
                        for (int j = 0; j < game.cols; j++) {
                            if (game.grid[i][j] == 1 && game.player[i][j] != 1
                             || game.grid[i][j] == -1 && game.player[i][j] == 1) {
                                cout << "提交失败, [" << (char)('A' + i) << "]行[" << (char)('a' + j) << "]列不符合要求";
                                i = game.rows;
                                break;
                            }
                        }
                    }
                }
            }
            else if (keycode1 == 113 || keycode1 == 81) {
                cct_showstr(9, hint_rows + game.rows + 7, "[读到Q/q] 游戏结束");
                break;
            }
            else {
                cct_showstr(9, hint_rows + game.rows + 7, "[读到键码] ");
                cout << keycode1 << "/" << keycode2 << "                                ";
            }
        }
    }
    
    //while (true) {
    //    int ret = cct_read_keyboard_and_mouse(mx, my, maction, keycode1, keycode2);
    //    
    //    if (ret == CCT_KEYBOARD_EVENT) {
    //        if (keycode1 == 13) { // 回车
    //            if (check_win(game)) {
    //                cct_showstr(1, data_start_y + game.rows * cell_height + 5, "恭喜！游戏成功！");
    //                break;
    //            } else {
    //                // 找第一个错误位置
    //                for (int i = 0; i < game.rows; i++) {
    //                    for (int j = 0; j < game.cols; j++) {
    //                        if ((game.grid[i][j] == 1 && game.player[i][j] != 1) ||
    //                            (game.grid[i][j] == 0 && game.player[i][j] == 1)) {
    //                            cct_showstr(1, data_start_y + game.rows * cell_height + 5, 
    //                                ("错误位置: " + string(1, 'A' + i) + string(1, 'a' + j)).c_str());
    //                            goto continue_game;
    //                        }
    //                    }
    //                }
    //            }
    //        } else if (keycode1 == 'q' || keycode1 == 'Q') {
    //            break;
    //        }
    //    } else if (ret == CCT_MOUSE_EVENT) {
    //        int grid_x = (mx - data_start_x) / cell_width;
    //        int grid_y = (my - data_start_y) / cell_height;
    //        
    //        if (grid_x >= 0 && grid_x < game.cols && grid_y >= 0 && grid_y < game.rows) {
    //            if (maction == MOUSE_LEFT_BUTTON_CLICK) {
    //                game.player[grid_y][grid_x] = (game.player[grid_y][grid_x] == 1) ? 0 : 1;
    //                draw_game_area(game);
    //            } else if (maction == MOUSE_RIGHT_BUTTON_CLICK) {
    //                game.player[grid_y][grid_x] = (game.player[grid_y][grid_x] == -1) ? 0 : -1;
    //                draw_game_area(game);
    //            }
    //        }
    //    }
    //    continue_game:;
    //}
    
    cct_disable_mouse();
    cct_setcursor(CURSOR_SHOWING);
}