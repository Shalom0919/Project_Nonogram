/* 2452098 计算机 赵崇治 */
#include <cstring>
#include <iostream>
#include <conio.h>
#include "pullze.h"
using namespace std;

int show_menu(){
    cct_cls();
    cct_setcolor();
    cct_setfontsize("新宋体", 16);
    cct_setconsoleborder(80, 32);
    cout << "┌─────────────────────────────────────────────────────────────┐" << endl;
    //cout << "│                        数织游戏                             │" << endl;
    cout << "│  A.内部数组，原样输出                                       │" << endl;
    cout << "│  B.内部数组，生成提示行列并输出                             │" << endl;
    cout << "│  C.内部数组，游戏版                                         │" << endl;
    cout << "├─────────────────────────────────────────────────────────────┤" << endl;
    cout << "│  D.n*n的框架(无分隔线)，原样输出                            │" << endl;
    cout << "│  E.n*n的框架(无分隔线)，含提示行列                          │" << endl;
    cout << "│  F.n*n的框架(无分隔线)，显示初始状态，鼠标移动可显示坐标    │" << endl;
    cout << "│  G.cmd图形界面完整版(无分隔线)                              │" << endl;
    cout << "├─────────────────────────────────────────────────────────────┤" << endl;
    cout << "│  H.n*n的框架(有分隔线)，原样输出                            │" << endl;
    cout << "│  I.n*n的框架(有分隔线)，含提示行列                          │" << endl;
    cout << "│  J.n*n的框架(有分隔线)，显示初始状态，鼠标移动可显示坐标    │" << endl;
    cout << "│  K.cmd图形界面完整版(有分隔线)                              │" << endl;
    cout << "├─────────────────────────────────────────────────────────────┤" << endl;
    cout << "│  Q.退出                                                     │" << endl;
    cout << "└─────────────────────────────────────────────────────────────┘" << endl;
    cout << "[请选择:] ";
        
    char op;
    while (true) {
        op = _getch();
        if ((op >= 'a' && op <= 'k') 
          ||(op >= 'A' && op <= 'K') 
          ||(op == 'q' || op == 'Q'))
            break;
    }
    cout << op << endl;
    cct_cls();
    if ((op >= 'a' && op <= 'k') || op == 'q')
        op = op - 32;
    return op - 'A' + 1;
}

void get_size_input(int& rows, int& cols)
{
    cout << "请输入区域大小(5/10/15) ：";
    while (true) {
        cin >> rows;
        if (cin.fail() || (rows != 5 && rows != 10 && rows != 15)) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "请输入区域大小(5/10/15) ：";
        } else {
            cin.ignore(1024, '\n');
            break;
        }
    }
    cols = rows;
}

bool input_coordinate(int& row, int& col, int max_row, int max_col)
{
    cout << "\n\n命令形式：Aa=等价于图形游戏中鼠标左键选择Aa位(区分大小写)" << endl;
    cout << "             不需要支持图形界面的右键打叉，再次输入Aa相当于清除" << endl;
    cout << "          X / x = 退出(新行仅有X / x，不分大小写)" << endl;
    cout << "          Y / y = 提交(新行仅有Y / y，不分大小写" << endl;
    cout << "          Z / z = 作弊(新行仅有Z / z，不分大小写)" << endl;
    cout << "          Ctrl + c 强制退出" << endl;
    cout<<"请输入 : ";
    char input[2];
    while (1) {
        input[0] = _getch();
        if (input[0] == 'X' || input[0] == 'x') {
            cout << input[0];
            return false;
        }
        else if (input[0] == 'Y' || input[0] == 'y') {
            row = -1;
            col = -1;
            return true;
        }
        else if (input[0] == 'Z' || input[0] == 'z') {
            row = -2;
            col = -2;
            return true;
        }
        else if (input[0] >= 'A' && input[0] < 'A' + max_row) {
            row = input[0] - 'A';
            cout << input[0];
            while (1) {
                input[1] = _getch();
                if (input[1] >= 'a' && input[1] < 'a' + max_row) {
                    cout << input[1] << endl;
                    col = input[1] - 'a';
                    return true;
                }
            }
        }
    }
}

void show_status(const char* message)
{
    cct_showstr(1, 35, "                                        ");
    cct_showstr(1, 35, message);
}

void clear_status_area()
{
    for (int i = 35; i < 40; i++) {
        cct_showstr(1, i, "                                        ");
    }
}