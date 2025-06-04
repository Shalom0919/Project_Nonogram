/* 2452098 计算机 赵崇治 */

#include <iostream>
#include <ctime>
#include <conio.h>
#include "pullze.h"
using namespace std;

int main()
{
    srand((unsigned int)time(NULL));
    while (true) {
        int choice = show_menu();
        if (choice == 17) {
            break;
        }

        GameState game = {};
        int rows, cols;
        get_size_input(rows, cols);

        init_game(game, rows, cols);
        generate_balls(game);
        calculate_hints(game);

        switch (choice) {
        case 1:
            print_game_text(game, false);
            break;
        case 2:
            print_game_text(game);
            break;
        case 3:
            cct_setconsoleborder(120, 40, 120, 350);
            print_game_text(game, true, false);
            play_text(game);
            break;
        case 4:
            init_game(game, rows, cols);
            generate_balls(game);
            draw_frame(game, 4);
            draw_game_area(game, 4);
            break;
        case 5:
            draw_fake_GUI(game, true, false, 5);
            draw_game_area(game, 5);
            break;
        case 6:
            draw_fake_GUI(game, true, false, 6);
            draw_game_area(game, 6);
            handle_mouse_input(game, 6);
            break;
        case 7:
            draw_fake_GUI(game, false, false, 7);
            console_game_loop(game);
            break;
        case 8:
            draw_frame(game, 4);
            draw_game_area(game, 4);
            break;
        case 9:
            break;
        case 10:
            handle_mouse_input(game, 10);
            break;
        case 11:
            console_game_loop(game);
            break;
        }

        cout << "\n本小题结束，请输入End继续...";
        char end;
        while (true) {
            end = _getch();
            if (end == 'e' || end == 'E')
                break;
        }
        cout << end;
        while (true) {
            end = _getch();
            if (end == 'n' || end == 'N')
                break;
        }
        cout << end;
        while (true) {
            end = _getch();
            if (end == 'd' || end == 'D')
                break;
        }
        cout << end;
    }
    return 0;
}
