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
		const int N = 7; // 格式化控制
		cct_setfontsize("新宋体", 24 - game.rows);
		cct_setconsoleborder(game.rows * 8 + 6, 256);

		cout << "\n      ";
		for (int i = 0; i < game.cols; i++) {
			cout << (char)('a' + i) << "       ";
		}
		cout << "\n  ";

		cct_setcolor(COLOR_HWHITE, 0);
		cout << "╔";

		for (int k = 1; k < game.rows; k++) {
			for (int i = 0; i < N; i++) {
				cout << "═";
			}
			cout << "╦";
		}
		cout << "═══════╗ \n";

		cct_setcolor();
		for (int i = 1; i < game.rows; i++) {
			for (int j = 1; j <= 3; j++) {
				if (j == 2) {
					cout << (char)('A' + i - 1) << " ";
				}
				else
					cout << "  ";
				cct_setcolor(COLOR_HWHITE, 0);
				cout << "║";
				for (int t = 1; t < game.rows; t++) {
					for (int i = 0; i < N; i++) {
						cout << " ";
					}
					cout << "║";
				}
				cout << "       ║ \n";
				cct_setcolor();
			}
			cout << "  ";
			cct_setcolor(COLOR_HWHITE, 0);
			cout << "╠";
			for (int k = 1; k < game.rows; k++) {
				for (int i = 0; i < N; i++) {
					cout << "═";
				}
				cout << "╬";
			}
			cout << "═══════╣ \n";

			cct_setcolor();
		}

		for (int j = 1; j <= 3; j++) {
			if (j == 2) {
				cout << (char)('A' + game.rows - 1) << " ";
			}
			else
				cout << "  ";
			cct_setcolor(COLOR_HWHITE, 0);
			cout << "║";
			for (int t = 1; t < game.rows; t++) {
				for (int i = 0; i < N; i++) {
					cout << " ";
				}
				cout << "║";
			}
			cout << "       ║ \n";
			cct_setcolor();
		}

		cct_setcolor();
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, 0);
		cout << "╚";
		for (int k = 1; k < game.rows; k++) {
			for (int i = 0; i < N; i++) {
				cout << "═";
			}
			cout << "╩";
		}
		cout << "═══════╝ ";
		cct_setcolor();
		cout << "\n\n"; // 这里一开始犯错了，换行没换下来

		/*for (int i = 0; i < game.rows; i++) {
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
		cout << "═╝ \n";*/
	}

	cct_setcolor();
}

void draw_fake_GUI(GameState& game,
	bool show_hint,
	bool show_seperator,
	int op) {

	if (op <= 7)
		cct_setfontsize("新宋体", 32 - game.rows / 5 * 2);
	cct_cls();
	if (op == 6) {
		cout << "测试键盘/鼠标左键/右键，回车退出\n";
	}
	else if (op == 7) {
		cout << "左键选〇/右键选×，Y/y提交，Z/z作弊，Q/q结束\n";
	}

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

	if (op <= 7) {
		for (int j = 0; j <= hint_cols; j++) {
			cout << "  ";
		}
		cout << "  ";
		cct_setcolor(COLOR_HWHITE, 0);
		cout << "╔";
		for (int i = 1; i < game.rows / 5 * 2; i++) {
			cout << "═════";
		}
		cout << "══════╗ \n";

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
					//if (game.grid[j][i]/* && show_answer*/) {
					//    cout << "  ";
					//}
					//else {
					cout << "  ";
					//}
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




	else if (op >= 8) {
		cct_setfontsize("新宋体", 24 - game.rows);
		cct_setconsoleborder(game.rows * 8 + hint_cols * 2 + 12, 256);
		for (int j = 0; j <= hint_cols; j++) {
			cout << "  ";
		}
		cout << "    ";
		cct_setcolor(COLOR_HWHITE, 0);
		cout << "╔";
		for (int i = 1; i < game.rows; i++) {
			cout << "════════";
		}
		cout << "═══════╗ " << endl;

		// 打印列提示
		for (int row = 0; row < hint_rows; row++) {
			cct_setcolor();
			cout << "    ";
			for (int j = 0; j <= hint_cols; j++)
				cout << "  ";
			cct_setcolor(COLOR_HWHITE, 0);
			cout << "║"; // 每行前导空白
			for (int j = 0; j < game.cols - 1; j++) {
				int hint_idx = row - (hint_rows - game.col_hint_count[j]);
				if (hint_idx >= 0 && hint_idx < game.col_hint_count[j]) {
					if (game.col_hints[j][hint_idx] < 10)
						cout << "   ";
					cout << game.col_hints[j][hint_idx] << "    ";
				}
				else {
					cout << "        ";
				}
			}
			int hint_idx = row - (hint_rows - game.col_hint_count[game.cols - 1]);
			if (hint_idx >= 0 && hint_idx < game.col_hint_count[game.cols - 1]) {
				if (game.col_hints[game.cols - 1][hint_idx] < 10)
					cout << "   ";
				cout << game.col_hints[game.cols - 1][hint_idx] << "   ";
			}
			else {
				cout << "       ";
			}
			cout << "║ " << endl;
		}

		// 分隔线
		cct_setcolor();
		for (int j = 0; j <= hint_cols; j++) {
			cout << "  ";
		}
		cout << "    ";
		cct_setcolor(COLOR_HWHITE, 0);
		cout << "╠";
		for (int i = 1; i < game.rows; i++) {
			cout << "════════";
		}
		cout << "═══════╣ " << endl;

		cct_setcolor();
		for (int j = 0; j <= hint_cols; j++) {
			cout << "  ";
		}
		cout << "    ";

		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "║   ";
		for (int i = 0; i < game.cols; i++) {
			cout << (char)('a' + i) << "   ";
			if (i != game.cols - 1)
				cout << "    ";
		}
		cout << "║ " << endl;

		cout << "╔"; // 上边框
		for (int j = 0; j < hint_cols; j++) {
			cout << "══";
		}
		cout << "═╦═══╬";

		const int N = 7; // 格式化控制

		cct_setcolor(COLOR_HWHITE, 0);

		for (int k = 1; k < game.rows; k++) {
			for (int i = 0; i < N; i++) {
				cout << "═";
			}
			cout << "╦";
		}
		cout << "═══════╣ \n";

		for (int i = 0; i < game.rows - 1; i++) {
			for (int j = 1; j <= 3; j++) {
				cout << "║";
				if (j == 2) {
					// 打印行标识和内容
					for (int col = 0; col < hint_cols; col++) {
						int hint_idx = col - (hint_cols - game.row_hint_count[i]);
						if (hint_idx >= 0 && hint_idx < game.row_hint_count[i]) {
							break;
						}
						else {
							cout << "  ";
						}
					}
					int k = 0;
					while (game.row_hints[i][k] > 0) {
						if (game.row_hints[i][k] < 10)
							cout << " ";
						cout << game.row_hints[i][k];
						k++;
					}
					cout << " ║  " << char('A' + i) << "║";
				}
				else {
					for (int i = 0; i < hint_cols; i++)
						cout << "  ";
					cout << " ║   ║";
				}

				for (int t = 1; t < game.rows; t++) {
					for (int i = 0; i < N; i++) {
						cout << " ";
					}
					cout << "║";
				}
				cout << "       ║ \n";
			}

			// 分隔线
			cout << "║";
			for (int i = 0; i < hint_cols; i++) {
				cout << "  ";
			}
			cout << " ║   ╠";
			for (int k = 1; k < game.rows; k++) {
				for (int i = 0; i < N; i++) {
					cout << "═";
				}
				cout << "╬";
			}
			cout << "═══════╣ \n";

		}

		for (int j = 1; j <= 3; j++) {
			cout << "║";
			if (j == 2) {
				// 打印行标识和内容
				for (int col = 0; col < hint_cols; col++) {
					int hint_idx = col - (hint_cols - game.row_hint_count[game.rows - 1]);
					if (hint_idx >= 0 && hint_idx < game.row_hint_count[game.rows - 1]) {
						break;
					}
					else {
						cout << "  ";
					}
				}

				int i = 0;
				while (game.row_hints[game.rows - 1][i] > 0) {
					if (game.row_hints[game.rows - 1][i] < 10)
						cout << " ";
					cout << game.row_hints[game.rows - 1][i];
					i++;
				}
				cout << " ║  " << (char)('A' + game.rows - 1) << "║";
			}
			else {
				cout << " ";
				for (int i = 0; i < hint_cols; i++)
					cout << "  ";
				cout << "║   ║";
			}
			for (int t = 1; t < game.rows; t++) {
				for (int i = 0; i < N; i++) {
					cout << " ";
				}
				cout << "║";
			}
			cout << "       ║ \n";
		}

		cout << "╚"; // 下边框
		for (int j = 0; j < hint_cols; j++) {
			cout << "══";
		}
		cout << "═╩═══╩";
		for (int k = 1; k < game.rows; k++) {
			for (int i = 0; i < N; i++) {
				cout << "═";
			}
			cout << "╩";
		}
		cout << "═══════╝ ";
		cct_setcolor();
		cout << "\n\n";
	}
}

void draw_big(const GameState& game, int part, int mode)
{
	if (part == 0) {
		cout << "      ";
		return;
	}
	if (part == 1)
		cout << "╔═══╗ ";
	if (part == 2 && mode == 1)
		cout << "║ 〇║ ";
	else if (part == 2 && mode == -1)
		cout << "║ ×║ ";
	if (part == 3)
		cout << "╚═══╝ ";
}

void draw_big_ball(GameState& game, int x, int y, int i, int j)
{
	cct_gotoxy(x + i * 8, y + j * 4 - 1);
	draw_big(game, 1, 1);
	cct_gotoxy(x + i * 8, y + j * 4);
	draw_big(game, 2, 1);
	cct_gotoxy(x + i * 8, y + j * 4 + 1);
	draw_big(game, 3, 1);
	cct_setcolor();
}

void draw_big_cross(GameState& game, int x, int y, int i, int j)
{
	cct_gotoxy(x + i * 8, y + j * 4 - 1);
	draw_big(game, 1, -1);
	cct_gotoxy(x + i * 8, y + j * 4);
	draw_big(game, 2, -1);
	cct_gotoxy(x + i * 8, y + j * 4 + 1);
	draw_big(game, 3, -1);
	cct_setcolor();
}

void draw_big_space(GameState& game, int x, int y, int i, int j)
{
	cct_gotoxy(x + i * 8, y + j * 4 - 1);
	draw_big(game, 0, 0);
	cct_gotoxy(x + i * 8, y + j * 4);
	draw_big(game, 0, 0);
	cct_gotoxy(x + i * 8, y + j * 4 + 1);
	draw_big(game, 0, 0);
	cct_setcolor();
}

void draw_game_area(GameState game, int op)
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
	else if (op == 8) {
		x = 4;
		y = 4;
	}
	else if (op >= 9) {
		x = hint_cols * 2 + 8;
		y = hint_rows + 5;
	}

	if (op <= 6) {
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
	else {
		for (int i = 0; i < game.rows; i++) {
			for (int j = 0; j < game.cols; j++) {
				if (game.grid[j][i] == 1) {
					cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
					draw_big_ball(game, x, y, i, j);
				}
			}
		}
		cct_setcolor();
		cct_gotoxy(0, hint_rows + game.rows * 4 + 4);
	}
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

		if (op == 6) {
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


		else {
			if (mx - hint_cols * 2 - 8 >= 0)
				grid_x = (mx - hint_cols * 2 - 8) / 8;

			int grid_y = -1024; // 还是要截断处理
			if (my - hint_rows - 4 >= 0)
				grid_y = (my - hint_rows - 4) / 4;

			if (ret == CCT_MOUSE_EVENT) {
				cct_showstr(9, hint_rows + game.rows * 4 + 5, "[当前光标] ");
				if (grid_x >= 0 && grid_x < game.cols && grid_y >= 0 && grid_y < game.rows) {
					if (maction == MOUSE_ONLY_MOVED && (grid_x != grid_oldx || grid_y != grid_oldy)) {
						char r[2];
						r[0] = 'A' + grid_y;
						r[1] = '\0';
						char l[2];
						l[0] = 'a' + grid_x;
						l[1] = '\0';
						cct_showstr(20, hint_rows + game.rows * 4 + 5, r);
						cct_showstr(21, hint_rows + game.rows * 4 + 5, "行");
						cct_showstr(23, hint_rows + game.rows * 4 + 5, l);
						cct_showstr(24, hint_rows + game.rows * 4 + 5, "列              ");
						grid_oldx = grid_x;
						grid_oldy = grid_y;
					}
					else if (maction == MOUSE_LEFT_BUTTON_CLICK) {
						cct_showstr(9, hint_rows + game.rows * 4 + 5, "[读到左键]                 ");
						char r[2];
						r[0] = 'A' + grid_y;
						r[1] = '\0';
						char l[2];
						l[0] = 'a' + grid_x;
						l[1] = '\0';
						cct_showstr(20, hint_rows + game.rows * 4 + 5, r);
						cct_showstr(21, hint_rows + game.rows * 4 + 5, "行");
						cct_showstr(23, hint_rows + game.rows * 4 + 5, l);
						cct_showstr(24, hint_rows + game.rows * 4 + 5, "列              ");
						cout << "\n         窗口：" << mx << "行 " << my << "列\n";
						break;
					}
					else if (maction == MOUSE_RIGHT_BUTTON_CLICK) {
						cct_showstr(9, hint_rows + game.rows * 4 + 5, "[读到右键]                 ");
						cout << "\n         窗口：" << mx << "行 " << my << "列\n";
						break;
					}
				}
				else {
					cct_showstr(20, hint_rows + game.rows * 4 + 5, "位置非法         ");
				}
			}
			else if (ret == CCT_KEYBOARD_EVENT) {
				if (keycode1 == 13) {
					cct_showstr(9, hint_rows + game.rows * 4 + 5, "[读到回车键]                 ");
					break;
				}
				else {
					cct_showstr(9, hint_rows + game.rows * 4 + 5, "[读到键码] ");
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
	}

	cct_disable_mouse();
	cct_setcursor(CURSOR_SHOWING);
}

void loop_SMALL(GameState& game)
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

						if (game.cheat_mode == false || (game.cheat_mode == true && game.grid[grid_y][grid_x] == 1)) {
							cct_setcolor(COLOR_HBLUE, 0);
						}
						else if (game.cheat_mode == true && game.grid[grid_y][grid_x] == 0) {
							cct_setcolor(COLOR_HRED, 0);
						}

						cout << "〇";
						cct_setcolor();
						game.player[grid_y][grid_x] = 1; // 选中
					}
					else {
						cct_gotoxy(mx - mx % 2, my);

						if (game.cheat_mode == false || (game.cheat_mode == true && game.grid[grid_y][grid_x] == 0)) {
							cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
							cout << "  ";
						}
						else if (game.cheat_mode == true && game.grid[grid_y][grid_x] == 1) {
							cct_setcolor(COLOR_WHITE, COLOR_BLACK);
							cout << "〇";
						}

						cct_setcolor();
						game.player[grid_y][grid_x] = 0; // 恢复
					}
				}
				else if (maction == MOUSE_RIGHT_BUTTON_CLICK) {
					cct_showstr(9, hint_rows + game.rows + 7, "[读到右键]                 ");
					if (game.player[grid_y][grid_x] != -1) {
						cct_gotoxy(mx - mx % 2, my);

						if (game.cheat_mode == false) {
							cct_setcolor(COLOR_HRED, COLOR_BLACK);
						}
						else if ((game.cheat_mode == true && game.grid[grid_y][grid_x] == 1)) {
							cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
						}
						else if (game.cheat_mode == true && game.grid[grid_y][grid_x] == 0) {
							cct_setcolor(COLOR_HRED, COLOR_BLACK);
						}

						cout << "×";
						cct_setcolor();
						game.player[grid_y][grid_x] = -1;
					}
					else {
						cct_gotoxy(mx - mx % 2, my);

						if (game.cheat_mode == true && game.grid[grid_y][grid_x] == 1) {
							cct_setcolor(COLOR_WHITE, COLOR_BLACK);
							cout << "〇";
						}
						else {
							cct_setcolor(COLOR_HWHITE, 0);
							cout << "  ";
						}

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
			if (keycode1 == 'y' || keycode1 == 'Y') {
				cct_showstr(9, hint_rows + game.rows + 7, "[读到提交键]                      ");
				if (check(game)) {
					Sleep(500);
					cct_showstr(9, hint_rows + game.rows + 7, "[提交成功]                                 ");
					break;
				}
				else {
					Sleep(500);
					cct_showstr(9, hint_rows + game.rows + 7, "提交错误，可用作弊模式查看    ");
				}
			}
			else if (keycode1 == 'z' || keycode1 == 'Z') {
				if (game.cheat_mode == false) {
					cct_showstr(9, hint_rows + game.rows + 7, "[作弊模式开]             ");
					game.cheat_mode = true;
					Sleep(500);
					int x = hint_cols * 2 + 6;
					int y = hint_rows + 5;
					for (int i = 0; i < game.rows; i++) {
						cct_gotoxy(x, i + y);
						for (int j = 0; j < game.cols; j++) {
							if (game.grid[i][j] == 1 && game.player[i][j] == 0) {
								cct_setcolor(COLOR_WHITE, COLOR_BLACK); // 1.有球没选圈
								cout << "〇";
							}
							else if (game.grid[i][j] == 1 && game.player[i][j] == 1) {
								cct_setcolor(COLOR_HBLUE, COLOR_BLACK); // 2.有球已选圈
								cout << "〇";
							}
							else if (game.grid[i][j] == 0 && game.player[i][j] == 1) {
								cct_setcolor(COLOR_HRED, COLOR_BLACK); // 3.无球已选圈
								cout << "〇";
							}
							else if (game.grid[i][j] == 0 && game.player[i][j] == -1) {
								cct_setcolor(COLOR_HRED, COLOR_BLACK); // 4.无球已选叉
								cout << "×";
							}
							else if (game.grid[i][j] == 1 && game.player[i][j] == -1) {
								cct_setcolor(COLOR_HBLUE, COLOR_BLACK); // 5.有球已选叉
								cout << "×";
							}
							else {
								cct_setcolor(COLOR_HWHITE, COLOR_BLACK); // 6.啥也没有
								cout << "  ";
							}
						}
					}
					cct_setcolor();
				}
				else {
					cct_showstr(9, hint_rows + game.rows + 7, "[作弊模式关]             ");
					game.cheat_mode = false;
					Sleep(500);
					int x = hint_cols * 2 + 6;
					int y = hint_rows + 5;
					for (int i = 0; i < game.rows; i++) {
						cct_gotoxy(x, i + y);
						for (int j = 0; j < game.cols; j++) {
							if (game.player[i][j] == 1) {
								cct_setcolor(COLOR_HBLUE, COLOR_BLACK); // 已选圈
								cout << "〇";
							}
							else if (game.player[i][j] == -1) {
								cct_setcolor(COLOR_HRED, COLOR_BLACK); // 已选叉
								cout << "×";
							}
							else {
								cct_setcolor(COLOR_HWHITE, COLOR_BLACK); // 啥也没有
								cout << "  ";
							}
						}
					}
					cct_setcolor();
				}
			}
			else if (keycode1 == 'q' || keycode1 == 'Q') {
				cct_showstr(9, hint_rows + game.rows + 7, "[读到Q/q] 游戏结束");
				break;
			}
			else {
				cct_showstr(9, hint_rows + game.rows + 7, "[读到键码] ");
				cout << keycode1 << "/" << keycode2 << "                                ";
			}
		}
	}

	cct_disable_mouse();
	cct_setcursor(CURSOR_SHOWING);
}

void loop_BIG(GameState& game)
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
	const int x = hint_cols * 2 + 8;
	const int y = hint_rows + 5;
	while (true) {
		int ret = cct_read_keyboard_and_mouse(mx, my, maction, keycode1, keycode2);
		int grid_oldx = -1024;
		int grid_oldy = -1024;

		int grid_x = -1024; // 单独处理0附近的截断向0取整问题
		if (mx - hint_cols * 2 - 8 >= 0)
			grid_x = (mx - hint_cols * 2 - 8) / 8;

		int grid_y = -1024; // 还是要截断处理
		if (my - hint_rows - 4 >= 0)
			grid_y = (my - hint_rows - 4) / 4;

		// 计算在格子内的相对位置
		int cell_x = (mx - hint_cols * 2 - 8) % 8;
		int cell_y = (my - hint_rows - 4) % 4;

		if (ret == CCT_MOUSE_EVENT) {
			cct_showstr(9, hint_rows + game.rows * 4 + 5, "[当前光标] ");
			if (grid_x >= 0 && grid_x < game.cols && grid_y >= 0 && grid_y < game.rows &&
				cell_x >= 0 && cell_x <= 5 && cell_y >= 0 && cell_y <= 2) {
				if (maction == MOUSE_ONLY_MOVED && (grid_x != grid_oldx || grid_y != grid_oldy)) {
					char r[2];
					r[0] = 'A' + grid_y;
					r[1] = '\0';
					char l[2];
					l[0] = 'a' + grid_x;
					l[1] = '\0';
					cct_showstr(20, hint_rows + game.rows * 4 + 5, r);
					cct_showstr(21, hint_rows + game.rows * 4 + 5, "行");
					cct_showstr(23, hint_rows + game.rows * 4 + 5, l);
					cct_showstr(24, hint_rows + game.rows * 4 + 5, "列              ");
					grid_oldx = grid_x;
					grid_oldy = grid_y;
				}
				else if (maction == MOUSE_LEFT_BUTTON_CLICK) {
					cct_showstr(9, hint_rows + game.rows * 4 + 5, "[读到左键]                 ");
					char r[2];
					r[0] = 'A' + grid_y;
					r[1] = '\0';
					char l[2];
					l[0] = 'a' + grid_x;
					l[1] = '\0';
					cct_showstr(20, hint_rows + game.rows * 4 + 5, r);
					cct_showstr(21, hint_rows + game.rows * 4 + 5, "行");
					cct_showstr(23, hint_rows + game.rows * 4 + 5, l);
					cct_showstr(24, hint_rows + game.rows * 4 + 5, "列                         ");
					if (game.player[grid_y][grid_x] != 1) {
						cct_gotoxy(mx - mx % 2, my);

						if (game.cheat_mode == false || (game.cheat_mode == true && game.grid[grid_y][grid_x] == 1)) {
							cct_setcolor(COLOR_HBLUE, 0);
						}
						else if (game.cheat_mode == true && game.grid[grid_y][grid_x] == 0) {
							cct_setcolor(COLOR_HRED, 0);
						}

						draw_big_ball(game, x, y, grid_x, grid_y);
						cct_setcolor();
						game.player[grid_y][grid_x] = 1; // 选中
					}
					else {
						cct_gotoxy(mx - mx % 2, my);

						if (game.cheat_mode == false || (game.cheat_mode == true && game.grid[grid_y][grid_x] == 0)) {
							cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
							draw_big_space(game, x, y, grid_x, grid_y);
						}
						else if (game.cheat_mode == true && game.grid[grid_y][grid_x] == 1) {
							cct_setcolor(COLOR_WHITE, COLOR_BLACK);
							draw_big_ball(game, x, y, grid_x, grid_y);
						}

						cct_setcolor();
						game.player[grid_y][grid_x] = 0; // 恢复
					}
				}
				else if (maction == MOUSE_RIGHT_BUTTON_CLICK) {
					cct_showstr(9, hint_rows + game.rows * 4 + 5, "[读到右键]                 ");
					if (game.player[grid_y][grid_x] != -1) {
						cct_gotoxy(mx - mx % 2, my);

						if (game.cheat_mode == false) {
							cct_setcolor(COLOR_HRED, COLOR_BLACK);
						}
						else if ((game.cheat_mode == true && game.grid[grid_y][grid_x] == 1)) {
							cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
						}
						else if (game.cheat_mode == true && game.grid[grid_y][grid_x] == 0) {
							cct_setcolor(COLOR_HRED, COLOR_BLACK);
						}

						draw_big_cross(game, x, y, grid_x, grid_y);
						cct_setcolor();
						game.player[grid_y][grid_x] = -1;
					}
					else {
						cct_gotoxy(mx - mx % 2, my);

						if (game.cheat_mode == true && game.grid[grid_y][grid_x] == 1) {
							cct_setcolor(COLOR_WHITE, COLOR_BLACK);
							draw_big_ball(game, x, y, grid_x, grid_y);
						}
						else {
							cct_setcolor(COLOR_HWHITE, 0);
							cout << "  ";
						}

						cct_setcolor();
						game.player[grid_y][grid_x] = 0;
					}
				}
			}
			else {
				cct_showstr(20, hint_rows + game.rows * 4 + 5, "位置非法         ");
			}
		}
		else if (ret == CCT_KEYBOARD_EVENT) {
			if (keycode1 == 'y' || keycode1 == 'Y') {
				cct_showstr(9, hint_rows + game.rows * 4 + 5, "[读到提交键]                      ");
				if (check(game)) {
					Sleep(500);
					cct_showstr(9, hint_rows + game.rows * 4 + 5, "[提交成功]                                 ");
					break;
				}
				else {
					Sleep(500);
					cct_showstr(9, hint_rows + game.rows * 4 + 5, "提交错误，可用作弊模式查看    ");
				}
			}
			else if (keycode1 == 'z' || keycode1 == 'Z') {
				if (game.cheat_mode == false) {
					cct_showstr(9, hint_rows + game.rows * 4 + 5, "[作弊模式开]             ");
					game.cheat_mode = true;
					Sleep(500);
					for (int i = 0; i < game.rows; i++) {
						for (int j = 0; j < game.cols; j++) {
							if (game.grid[i][j] == 1 && game.player[i][j] == 0) {
								cct_setcolor(COLOR_WHITE, COLOR_BLACK); // 1.有球没选圈
								draw_big_ball(game, x, y, j, i);
							}
							else if (game.grid[i][j] == 1 && game.player[i][j] == 1) {
								cct_setcolor(COLOR_HBLUE, COLOR_BLACK); // 2.有球已选圈
								draw_big_ball(game, x, y, j, i);
							}
							else if (game.grid[i][j] == 0 && game.player[i][j] == 1) {
								cct_setcolor(COLOR_HRED, COLOR_BLACK); // 3.无球已选圈
								draw_big_ball(game, x, y, j, i);
							}
							else if (game.grid[i][j] == 0 && game.player[i][j] == -1) {
								cct_setcolor(COLOR_HRED, COLOR_BLACK); // 4.无球已选叉
								draw_big_cross(game, x, y, j, i);
							}
							else if (game.grid[i][j] == 1 && game.player[i][j] == -1) {
								cct_setcolor(COLOR_HBLUE, COLOR_BLACK); // 5.有球已选叉
								draw_big_cross(game, x, y, j, i);
							}
							else {
								cct_setcolor(COLOR_HWHITE, COLOR_BLACK); // 6.啥也没有
								draw_big_space(game, x, y, j, i);
							}
						}
					}
					cct_setcolor();
				}
				else {
					cct_showstr(9, hint_rows + game.rows * 4 + 5, "[作弊模式关]             ");
					game.cheat_mode = false;
					Sleep(500);
					for (int i = 0; i < game.rows; i++) {
						for (int j = 0; j < game.cols; j++) {
							if (game.player[i][j] == 1) {
								cct_setcolor(COLOR_HBLUE, COLOR_BLACK); // 已选圈
								draw_big_ball(game, x, y, j, i);
							}
							else if (game.player[i][j] == -1) {
								cct_setcolor(COLOR_HRED, COLOR_BLACK); // 已选叉
								draw_big_cross(game, x, y, j, i);
							}
							else {
								cct_setcolor(COLOR_HWHITE, COLOR_BLACK); // 啥也没有
								draw_big_space(game, x, y, j, i);
							}
						}
					}
					cct_setcolor();
				}
			}
			else if (keycode1 == 'q' || keycode1 == 'Q') {
				cct_showstr(9, hint_rows + game.rows * 4 + 5, "[读到Q/q] 游戏结束");
				break;
			}
			else {
				cct_showstr(9, hint_rows + game.rows * 4 + 5, "[读到键码] ");
				cout << keycode1 << "/" << keycode2 << "                                ";
			}
		}
	}

	cct_disable_mouse();
	cct_setcursor(CURSOR_SHOWING);
}